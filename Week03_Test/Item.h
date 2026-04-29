#pragma once
#include <string>
using namespace std;

enum class ItemType { Weapon, Armor, Consumable };

class Item
{
public:
    string name;
    ItemType type;
    
    Item(const string &name, const ItemType type) : name(name), type(type) {}
    virtual ~Item(); // 소멸자 타이밍 확인용

};
