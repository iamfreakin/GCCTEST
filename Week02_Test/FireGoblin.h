#pragma once
#include "Monster.h"

class FireGoblin : public Monster
{
public:
    FireGoblin(std::string n, int str, int dex, int vit, int eng, int lv);
    
    int Attack() const override;
    std::string GetAttackMessage() const override { return "Fire Enhanced Attack!"; }
};
