
#ifndef INVENTORY_HPP
#define INVENTORY_HPP


#include <string>
#include <map>

#include "item_mech.hpp"


class Inventory {
public:

    std::string inv_font_location = "../assets/fonts/BigBlueTerm.ttf";
    Font inv_font;

    std::map<std::string, Item> inventory_list; 


    void          init();
    std::string   look_item(const Vector2& mouse_position) const;
    std::string   pickup_item(const std::map<std::string, Item>& room_items, const Vector2& mouse_position);
    std::string   drop_item(std::map<std::string, Item>& room_items, const Vector2& mouse_position);
    void          render() const;

private:
    struct Inv_Bar {
        Vector2 slot_1 = {47, 70};
        Vector2 slot_2;
        Vector2 slot_3;
        Vector2 slot_4;
        Vector2 slot_5;      
    };

    Inv_Bar inv_bar = {};

};


#endif // !INVENTORY_HPP
