#pragma once
#include <string>
#include <iostream>
#include "Player.h"
using namespace std;

class Mercenary
{
public:
    string name;
    int attackDamage;
    weak_ptr<Player> owner;
    
    Mercenary(const string& name, int atk, shared_ptr<Player> owner);
    ~Mercenary();
    
    int Attack() const { return attackDamage; }
    bool IsOwnerAlive() const { return !owner.expired(); } // 주인이 살아 있는지 확인
};
