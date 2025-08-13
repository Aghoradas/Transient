#include "../mechanics/scene_mech.hpp"



void SceneFactory::create(std::map<std::string, std::shared_ptr<SceneOperations>>& scene_registry, const int screen_width, const int screen_height) {
    rapidjson::Document scenes_json;
    std::cout << "Loading scene from file: " << scenes_location << std::endl;
    std::ifstream data_file(scenes_location);

    rapidjson::IStreamWrapper data_stream(data_file);
    scenes_json.ParseStream(data_stream);

    std::string scene_id;

    // Value assignments from json file
    for (auto member = scenes_json.MemberBegin(); member != scenes_json.MemberEnd(); ++member) {

        auto room(std::make_shared<SceneOperations>());
        room->init();
        room->screen_width = screen_width;
        room->screen_height = screen_height;

        const rapidjson::Value &member_name = member->value;
        scene_id = member_name["scene_id"].GetString();

        if (member_name.HasMember("scene_name")) {
            assert(member_name["scene_name"].IsString());
            room->scene_name = member_name["scene_name"].GetString();
            std::cout << "Scene name: " << room->scene_name << std::endl;
        } else {
            std::cout << "No scene name found: " << scenes_json["room_1"].GetType() << std::endl;
        }
        if (member_name.HasMember("background")) {
            room->background_path = member_name["background"].GetString();
        }
        if (member_name.HasMember("midground")) {
            room->midground_path = member_name["midground"].GetString();
        }
        if (member_name.HasMember("exit_rectangle")) {
            std::vector<float> rec_points;

            for (auto& exit : member_name["exit_rectangle"].GetObject()) {
                const auto& exit_array = exit.value;

                for (auto& exit_rec : exit_array.GetArray()) {
                    float temp = exit_rec.GetFloat();
                    rec_points.emplace_back(temp);
                }
                Rectangle rec_temp = {rec_points[0], rec_points[1], rec_points[2], rec_points[3]};
                room->exit_scene[exit.name.GetString()] = rec_temp;
                rec_points.clear();


            }

        }
        if (member_name.HasMember("zone_points")) {
            room->zone_points = member_name["zone_points"].GetInt();
        }
        if (member_name.HasMember("walk_zone")) {
            Vector2 new_point;
            int components = room->zone_points * 2;
            for (int points = 0; points < components; points += 2) {
                float component_1 = member_name["walk_zone"][points].GetFloat();
                float component_2 = member_name["walk_zone"][points + 1].GetFloat();
                new_point = {component_1, component_2};
                room->walk_zone.emplace_back(new_point);
                std::cout << "new_point: ";
            }
        }

        if (member_name.HasMember("next_room")) {
            for (auto& next : member_name["next_room"].GetObject()) {
                std::string direction = next.name.GetString();
                std::string next_room_name = next.value.GetString();
                room->next_room[direction] = next_room_name;
            }
        }

        if (member_name.HasMember("items")) {
            std::cout << "\n-loading items from json" << std::endl;
            auto member_name_json = member_name["items"].GetObject();
            for (auto item = member_name_json.begin(); item != member_name_json.end(); ++item) {
                auto& json_item = item->value;
                std::cout << "\n-items: " << json_item[0].GetString() << std::endl;
                std::cout << "-file_location: " << json_item[1].GetString();
                Item new_item;
                new_item.item_name = json_item[0].GetString();
                new_item.description = json_item[1].GetString();
                new_item.file_location = json_item[2].GetString();
                new_item.location_x = json_item[3].GetFloat();
                new_item.location_y = json_item[4].GetFloat();
                room->room_items[new_item.item_name] = new_item;
            }
        }

        if (member_name.HasMember("scene_text")) {
            room->text_location = member_name["scene_text"].GetString();
        }

        scene_registry[scene_id] = room;
        std::cout << "Scene registered: " << scene_registry[scene_id]->scene_name << std::endl;
    }
}
