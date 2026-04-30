#include "FireGoblin.h"

FireGoblin::FireGoblin(const string& name, const MonsterData& data, int lv)
    : Monster(name, data, lv) {}

int FireGoblin::Attack() const
{
    return (int)(attackDamage * 1.5f);
}