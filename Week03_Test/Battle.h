#pragma once
#include "Monster.h"
#include "Player.h"

class Battle
{
private:
    Player& player;
    Monster& monster;
    string combatMessage;
    
public:
    Battle(Player& player, Monster& monster);
    bool Run();
};
