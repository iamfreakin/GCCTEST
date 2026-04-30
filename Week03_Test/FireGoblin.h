#pragma once
#include "Monster.h"

class FireGoblin : public Monster
{
public:
    FireGoblin(const string& name, const MonsterData& data , int lv = 1);
    
    int Attack() const override;
    string GetAttackMessage() const override { return " [Fire!]"; }
};
