#include "../mechanics/player.hpp"
#include <raylib.h>


void Player::initialize() {

    // LOADING player sprites
    idle = LoadTexture("../assets/player_idle.png");
    idle.height *= 3;
    idle.width *= 3;

    walk = LoadTexture("../assets/player_walk.png");
    walk.height *= 3;
    walk.width *= 3;

    width = static_cast<float>(idle.width) / static_cast<float>(frame_count);
    height = static_cast<float>(idle.height);


    animation_state = idle;
    src = {
        static_cast<float>(current_frame) * width,
        0,
        width,
        height
    };
    origin = {0, 0};
    dest = {
        position.x,
        position.y,
        width,
        height
    };
}

void Player::new_scene(std::string& exit_location) {
    is_walking = false;
    animation_state = idle;
    if (exit_location == "right") {
        position = {player_enter_x, player_enter_y};
        destination = position;
        mouse_click_target = position;
        src = {
            static_cast<float>(current_frame) * width,
            0,
            width,
            height
        };
        dest = {
            position.x,
            position.y,
            width,
            height
        };
    } else if (exit_location == "left") {
        position = {790, player_enter_y};
        destination = position;
        mouse_click_target = position;
        src = {
            static_cast<float>(current_frame) * width,
            0,
            -width,
            height
        };
        dest = {
            position.x,
            position.y,
            width,
            height
        };
    }
}

void Player::update(float& frame_time) {

    // MOVEMENT toward destination
    if (is_walking) {
        Vector2 direction = {destination.x - position.x, destination.y - position.y};
        const float distance = get_distance(position, destination);

        // Normalize direction
        if (distance > 1.0f) {
            direction.x /= distance;
            direction.y /= distance;

            const float speed = 100.0f * GetFrameTime();
            position.x += direction.x * speed;
            position.y += direction.y * speed;
        } else {
            is_walking = false;
        }
    }

    // WILL direction mouse-clicked with this.
    if (destination.x < position.x) {
        src = {
            static_cast<float>(current_frame) * width,
            0,
            -width,
            height
        };
    } else if (destination.x > position.x) {
        src = {
            static_cast<float>(current_frame) * width,
            0,
            width,
            height
        };
    }
    dest = {
        position.x,
        position.y,
        width - 8,
        height
    };

    // Animation
    if (is_walking) {
        frame_time = .15f;
        animation_state = walk;
    }
    if (!is_walking) {
        frame_time = .3f;
        animation_state = idle;
    }
    if (frame_timer >= frame_time) {
        frame_timer = 0.0f;
        current_frame+=1;
        if (current_frame >= frame_count) {
            current_frame = 1;
        }
    }


}

void Player::render() {

    DrawTexturePro(animation_state, src, dest, origin, 0.0f, WHITE);


}

void Player::unload() {
    UnloadTexture(idle);
    UnloadTexture(walk);
    UnloadTexture(animation_state);
}


