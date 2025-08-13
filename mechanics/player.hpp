
#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <map>
#include <vector>
#include <cmath>
#include <raylib.h>

#include "inventory.hpp"

class Player {
public:

    // PLAYER ANIMATIONS
    const int   frame_count = 10;

    Texture2D   idle;
    Texture2D   walk;
    Texture2D   animation_state;

    // Setup for sprite animation frames.
    float       width;
    float       height;
    int         current_frame = 0;
    float       frame_timer = 0.0f;

    // Player start position
    float       player_enter_x = 30.0f;
    float       player_enter_y = 575.0f;
    Vector2     position = {player_enter_x, player_enter_y};
    Vector2     destination = {player_enter_x, player_enter_y};


    // Player Boxes
    Rectangle   src = {};
    Vector2     origin = {};
    Rectangle   dest = {};

    Vector2     mouse_click_target;

    bool        is_walking = false;
    std::string dialogue = " ";

    // Utility function to get distance between two points
    static float get_distance(const Vector2& player_position, const Vector2& destination) {
        return sqrtf(powf(destination.x - player_position.x, 2) + powf(destination.y - player_position.y, 2));
    }

    void initialize();
    void new_scene(std::string& new_room);
    void update(float& frame_time);
    void render() const;
    void unload();

};
#endif
