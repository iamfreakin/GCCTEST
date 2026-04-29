#pragma once
#include "Monster.h"
#include "Player.h"

class Battle
{
private:
    Player& player;
    Monster& monster;
    shared_ptr<Mercenary> mercenary; // 없는 경우 nullptr
    string combatMessage;
    
public:
    Battle(Player& player, Monster& monster, shared_ptr<Mercenary> mercenary = nullptr);
    bool Run();
};
