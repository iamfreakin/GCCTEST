#include "Mercenary.h"

#include <iostream>

Mercenary::Mercenary(const std::string name, int atk, shared_ptr<Player> owner)
    : name(name), attackDamage(atk), owner(owner)
{
    std::cout << "[용병고용]" << name << " 가 합류했습니다." << '\n';
}

Mercenary::~Mercenary()
{
    std::cout << "[용병소멸]" << name << " 가 소멸되었습니다." << '\n';
}
