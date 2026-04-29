#pragma once
#include <memory>
#include <string>

#include "Player.h"

class Mercenary
{
public:

    std::string name;
    int attackDamage;
    shared_ptr<Player> owner;
    
    Mercenary(const std::string name, int atk, shared_ptr<Player> owner);
    virtual ~Mercenary();
    
    int Attack() const { return attackDamage; }
    bool isOwnerAilve() const { return owner != nullptr; } // 주인이 살아있는지 확인
    
};
