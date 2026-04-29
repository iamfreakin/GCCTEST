#include "Barbarian.h"

Barbarian::Barbarian(const string& name, bool isHardcore)
    : Player(name, "Barbarian", isHardcore, 80, 40, 70, 20) {}

int Barbarian::Attack() const
{
    return (int)(attackDamage * 1.2f);
}
