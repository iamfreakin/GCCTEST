#pragma once
#include <string>
using namespace std;

enum class ItemType { Weapon, Armor, Consumable, ETC };

class Item
{
public:
    string name;
    ItemType type;
    
    Item() : name(""), type(ItemType::Consumable) {}
    Item(const string &name, const ItemType type) : name(name), type(type) {}
};
