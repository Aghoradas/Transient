#include "../mechanics/scene_mech.hpp"


void parse_scene_text(std::string& text_location, std::map<std::string, std::vector<std::string>>& scene_text) {
    using namespace rapidjson;

    Document text_json;
    std::cout << "-loading text_location from file: " << text_location << std::endl;
    std::ifstream text_file(text_location);


    IStreamWrapper text_stream(text_file);
    text_json.ParseStream(text_stream);

    std::vector<std::string> text_list;
    std::string content;

    std::cout << "-initiating parse stream loop" << std::endl;
    for (auto member = text_json.MemberBegin(); member != text_json.MemberEnd(); ++member) {
        std::cout << "-beginning with: " << member->name.GetString() << std::endl;

        const Value& member_name = member->value;
        std::cout << "-member value created" << std::endl;

        if (member_name.HasMember("enter_room") && member_name["enter_room"].IsString()) {
            content = member_name["enter_room"].GetString();
            scene_text["enter_room"].emplace_back(content);
        } else {
            std::cout << "-enter_room not loaded" << std::endl;
        }
        if (member_name.HasMember("look_self") && member_name["look_self"].IsString()) {
            content = member_name["look_self"].GetString();
            scene_text["look_self"].emplace_back(content);
        } else {
            std::cout << "-look_self not loaded" << std::endl;
        }

    }

}

void SceneOperations::init() {

    for (auto& item : room_items) {
        item.second.init();
    }

}

void SceneOperations::entering() {
    printf("-entering scene\n");

    // Loading assets
    printf("-loading textures\n");
    background = LoadTexture(background_path.c_str());
    midground = LoadTexture(midground_path.c_str());
        for (auto& item : room_items) {
            std::cout << "-loading items to scene" << std::endl;
            item.second.init();
        }

    background.width = screen_width;
    background.height = screen_height;
    midground.width = screen_width;
    midground.height = screen_height;

    parse_scene_text(text_location, scene_text);
    dialogue = scene_text["enter_room"].at(0);
}

void SceneOperations::exiting() {
    for (auto& item : room_items) {
        std::cout << "-unloading" << item.second.item_name << std::endl;
        item.second.unload();
    }
    UnloadTexture(midground);
    UnloadTexture(background);
}

void SceneOperations::update(float delta_time) {

}

void SceneOperations::render() {

    DrawTexture(background, 0, 0, WHITE);
    DrawTexture(midground, 0, 0, WHITE);

    for (auto& item : room_items) {
        item.second.render();
    }
}
