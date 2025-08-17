
#ifndef SCENE_MECH_HPP
#define SCENE_MECH_HPP

#include <map>
#include <string>
#include <memory>
#include <raylib.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/document.h>

#include "../mechanics/item_mech.hpp"
#include "../mechanics/player.hpp"



/* SCENE CLASS
*****************/
class SceneOperations {
public:
    ~SceneOperations() {
        UnloadTexture(background);
        UnloadTexture(midground);
    }

    std::string                                     scene_name;
    int                                             screen_width;
    int                                             screen_height;

    void init();
    void entering();
    void exiting() const;
    void update(float delta_time) const;
    void render() const;

    bool loaded = false;
    Texture2D                                       background;
    Texture2D                                       midground;

    std::map<std::string, Item>                     room_items;

    std::string                                     text_location;
    std::map<std::string, std::vector<std::string>> scene_text;
    std::string                                     dialogue;

    std::map<std::string, std::string>              next_room;
    std::map<std::string, Rectangle>                exit_scene;
    int                                             zone_points;
    std::vector<Vector2>                            walk_zone;

    std::string                                     background_path;
    std::string                                     midground_path;

};


/* SCENE FACTORY
*******************/
class SceneFactory {
public:
    std::string scenes_location = "../library/scenes_file.json";
    void create(std::map<std::string, std::shared_ptr<SceneOperations>>& scene_registry, int screen_width, int screen_height);
};


/* SCENE ENGINE
******************/
class SceneEngine {
public:
    int window_width = 0;
    int window_height = 0;

    SceneEngine() = default;
    ~SceneEngine() = default;

    Font in_game_font = GetFontDefault();
    float frame_time = 0.0f;

    // Inventory
    Inventory   inventory;

    void init(int width, int height);
    void register_scenes();
    void switch_scene(std::string& new_room);
    void update(float delta_time);
    void render() const;
    void handle_mouse();

    std::shared_ptr<SceneOperations> current_scene = nullptr;
    std::shared_ptr<Player> player = nullptr;

    std::string temp_interaction;


    // UI - init
    Texture2D ui_base = LoadTexture("../assets/player_bar.png");
    int ui_y_begin = 695;
    int ui_x_begin = 0;

private:

    float base_frame_time = 2.0f;
    std::string json_location;
    std::map<std::string, std::shared_ptr<SceneOperations>> scene_registry;

};


#endif
