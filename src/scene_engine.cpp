#include "../mechanics/scene_mech.hpp"



void SceneEngine::init(int width, int height) {
    printf("Initializing scene engine...\n");
    in_game_font = LoadFont("../assets/fonts/BigBlueTerm.ttf");
    window_width = width;
    window_height = height;
    register_scenes();
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

void SceneEngine::render() const {
    current_scene->render();
    player->render();
}

void SceneEngine::handle_mouse() {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        // Left click to move
        if (CheckCollisionPointPoly(GetMousePosition(), &current_scene->walk_zone[0], current_scene->zone_points)) {
            player->destination = GetMousePosition();
            player->destination.x -= player->width/2;
            player->destination.y -= player->height;
            player->is_walking     = true;
            temp_interaction       = player->dialogue;
        }
    }
    if (!current_scene->exit_scene.empty()) {
        std::string exit_location;
        if (CheckCollisionRecs(player->dest, current_scene->exit_scene["right"])) {
            exit_location = "right";
            std::string new_room = current_scene->next_room[exit_location];
            switch_scene(new_room);
            player->new_scene(exit_location);
        } else if (CheckCollisionRecs(player->dest, current_scene->exit_scene["left"])) {
            exit_location = "left";
            std::string new_room = current_scene->next_room[exit_location];
            switch_scene(new_room);
            player->new_scene(exit_location);
        }
    }
    if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
        // Right click to interact/look
        Vector2 clicked = GetMousePosition();
        current_scene->dialogue = "Looking at (" + std::to_string(static_cast<int>(clicked.x)) +
          "," + std::to_string(static_cast<int>(clicked.y)) + ")";

        // You can use a scene grid or collision detection to trigger interactions here
        if (CheckCollisionPointRec(clicked, player->dest)) {
            current_scene->dialogue = current_scene->scene_text["look_self"].at(0);
        }
    }
}

