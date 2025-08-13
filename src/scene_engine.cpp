#include "../mechanics/scene_mech.hpp"
#include <raylib.h>



void SceneEngine::init(int width, int height) {
    printf("Initializing scene engine...\n");
    in_game_font = LoadFont("../assets/fonts/BigBlueTerm.ttf");
    window_width = width;
    window_height = height;
    register_scenes();
    current_scene->init();
}

void SceneEngine::register_scenes() {
    printf("Registering scenes...\n");
    SceneFactory factory;
    factory.create(scene_registry, window_width, window_height);
    current_scene = scene_registry["room1"];
}

void SceneEngine::switch_scene(std::string& new_room) {
    current_scene = scene_registry[new_room];
    current_scene->init();
    current_scene->entering();
}

void SceneEngine::update(const float delta_time) {
    float frame_time = base_frame_time / delta_time;
    current_scene->update(frame_time);
    player->frame_timer += delta_time;
    player->update(frame_time);
}


void SceneEngine::handle_mouse() {
    if (IsKeyDown(KEY_LEFT_CONTROL)) {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            const Vector2 mouse_position = GetMousePosition();

            const auto x_distance = static_cast<unsigned int>(mouse_position.x - player->position.x);
            const auto y_distance = static_cast<unsigned int>(mouse_position.y - player->position.y);
            std::cout << x_distance << ", " << y_distance << std::endl;
            if (x_distance < 120 && y_distance < 120) {
                const std::string removed_item = inventory.pickup_item(current_scene->room_items, mouse_position);
                current_scene->room_items.erase(removed_item);
            }
        }

    } else if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        // Left click to move
        if (CheckCollisionPointPoly(GetMousePosition(), &current_scene->walk_zone[0], current_scene->zone_points)) {
            current_scene->dialogue = "";
            player->destination = GetMousePosition();
            player->destination.x -= player->width/2;
            player->destination.y -= player->height;
            player->is_walking     = true;
        }
    }

    if (!current_scene->exit_scene.empty()) {
        std::string exit_location;
        if (CheckCollisionRecs(player->dest, current_scene->exit_scene["right"])) {
            exit_location = "right";
            std::string new_room = current_scene->next_room[exit_location];
            current_scene->exiting();
            switch_scene(new_room);
        player->new_scene(exit_location);
        } else if (CheckCollisionRecs(player->dest, current_scene->exit_scene["left"])) {
            exit_location = "left";
            std::string new_room = current_scene->next_room[exit_location];
            current_scene->exiting();
            switch_scene(new_room);
            player->new_scene(exit_location);
        }
    }
    if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
        // Right click to interact/look
        const Vector2 mouse_position = GetMousePosition();

        if (mouse_position.y > current_scene->screen_height) {
            current_scene->dialogue = inventory.look_item(mouse_position);
            return;
        }
        current_scene->dialogue = "Looking at (" + std::to_string(static_cast<int>(mouse_position.x)) +
          "," + std::to_string(static_cast<int>(mouse_position.y)) + ")";

        // You can use a scene grid or collision detection to trigger interactions here
        if (CheckCollisionPointRec(mouse_position, player->dest)) {
            current_scene->dialogue = current_scene->scene_text["look_self"].at(0);
            return;
        }
        for (auto& item : current_scene->room_items) {
            if (CheckCollisionPointRec(mouse_position, item.second.click_box)) {
                current_scene->dialogue = item.second.mouse_handle(mouse_position);
                return;
            }
        }
    }
}

void SceneEngine::render() const {

    current_scene->render();
    player->render();

    // DRAW ui_base
    DrawTexture(ui_base, ui_x_begin, ui_y_begin, WHITE);

    inventory.render();

}
