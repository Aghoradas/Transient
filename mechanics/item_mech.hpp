
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
        icon.height -= static_cast<int>(static_cast<float>(icon.height) * 0.50f);
        icon.width -= static_cast<int>(static_cast<float>(icon.width) * 0.25f);

        click_box = {
            location_x,
            location_y,
            static_cast<float>(sprite.width),
            static_cast<float>(sprite.height)
        };
    }

    std::string mouse_handle(const Vector2& click) {
        if (CheckCollisionPointRec(click, click_box) && !was_clicked) {
            was_clicked = true;
            return description;
        }
        if (CheckCollisionPointRec(click, click_box) && was_clicked) {
            was_clicked = false;
            return "Oh wow! They're right about you. You are relentless.";
        }
        return "";

    }
    void icon_render() const {
        DrawTextureV(icon, (Vector2){344, 705}, GRAY);
    }
    void render() const {
        DrawTextureV(sprite, (Vector2){location_x, location_y}, WHITE);
    }
    void unload() const {
        UnloadTexture(sprite);
    }
};

#endif
