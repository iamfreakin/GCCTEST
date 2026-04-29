#pragma once
#include "Player.h"

class Barbarian : public Player
{
public:
    Barbarian(const string& name, bool isHardcore);
    
    int Attack() const override;
    string GetAttackMessage() const override { return " [Bash!]"; }
};
