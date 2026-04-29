#include "Item.h"

Item::Item() : name("Empty"), type(ItemType::None), value(0) {}

Item::Item(std::string n, ItemType t, int v, int g) 
    : name(n), type(t), value(v) {}