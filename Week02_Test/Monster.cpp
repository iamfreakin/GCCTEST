#include "Monster.h"

Monster::Monster() : Character("", 0, 0, 0, 0, 1), active(false), expReward(0) {}

void Monster::Spawn(std::string n, int h, int a, int xp)
{
    name = n;
    hp = h;
    maxHp = h;
    attackDamage = static_cast<float>(a);
    
    // Monster 고유 정보 설정
    expReward = xp;
    active = true;
}