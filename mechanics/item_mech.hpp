
#ifndef ITEM_MECH_HPP
#define ITEM_MECH_HPP

#include <string>
#include <iostream>
#include <raylib.h>


/* ITEM CLASS
****************/
class Item {
public:
    std::string     file_location;


    Texture2D       sprite;
    Texture2D       icon;
    Rectangle       click_box;

    std::string     item_name;
    std::string     description;

    float           location_x;
    float           location_y;

    bool            was_clicked = false;


    void init() {
        std::cout << "-item init" << item_name << std::endl;

        sprite = LoadTexture(file_location.c_str());
        sprite.height *= 2;
        sprite.width  *= 2;

        icon = sprite;
        icon.height -= icon.height * .50;
        icon.width -= icon.width * .25;

        click_box = {
            location_x,
            location_y,
            static_cast<float>(sprite.width),
            static_cast<float>(sprite.height)
        };
    }

    std::string mouse_handle(Vector2 click) {
        if (CheckCollisionPointRec(click, click_box) && !was_clicked) {
            was_clicked = true;
            return "Ouch, that hurt!";
        } else if (CheckCollisionPointRec(click, click_box) && was_clicked) {
            return "Oh wow! They're right about you. You are relentless.";
        }
        return " ";

    }
    void icon_render() {
        DrawTexture(icon, 344, 705, GRAY);
    }
    void render() {
        DrawTextureV(sprite, (Vector2){location_x, location_y}, WHITE);
    }
    void unload() const {
        UnloadTexture(sprite);
    }
};

#endif
