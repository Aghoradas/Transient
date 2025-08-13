#include "../mechanics/inventory.hpp"


/* INVENTORY 
***************/

void Inventory::init() {
    inv_font = LoadFont(inv_font_location.c_str());
}


std::string Inventory::look_item(const Vector2& mouse_position) const {

    for (const auto& item : inventory_list) {
        if (CheckCollisionPointRec(mouse_position, item.second.click_box)) {
            return item.first;
        }
    }
    return "";
}


std::string Inventory::pickup_item(const std::map<std::string, Item>& room_items, const Vector2& mouse_position) {
    for (const auto& item : room_items) {

        if (CheckCollisionPointRec(mouse_position, item.second.click_box)) {
            Item exchange_item = item.second;
            exchange_item.location_x = inv_bar.slot_1.x;
            exchange_item.location_y = inv_bar.slot_1.y;

            inventory_list[exchange_item.item_name] = exchange_item;

            const std::string picked_up = "PICKED UP: " + exchange_item.item_name;
            std::cout << picked_up << std::endl;
            return exchange_item.item_name;
        }

    }
    return " ";
}


std::string Inventory::drop_item(std::map<std::string, Item>& room_items, const Vector2& mouse_position) {
    for (const auto& item : inventory_list) {
        if (CheckCollisionPointRec(mouse_position, item.second.click_box)) {
            const Item exchange_item = item.second;
            room_items[exchange_item.item_name] = exchange_item;
            inventory_list.erase(exchange_item.item_name);
            return item.first;
        }
    }
    return "";
}

void Inventory::render() const {
    for (auto& item : inventory_list) {
        item.second.icon_render();
    }
}
