#include "Monster.h"

Monster::Monster() : name(""), hp(0), maxHp(0), attackDamage(0), active(false) {}

void Monster::Spawn(string n, int h, int a)
{
    name = n;
    hp = h;
    maxHp = h;
    attackDamage = a;
    active = true;
}

void Monster::TakeDamage(int damage) 
{
    hp = std::max(0, hp - damage);
}