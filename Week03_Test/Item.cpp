#include "Item.h"
#include <iostream>

Item::~Item()
{
    cout << "[아이템 소멸]" << name << "\n";
}