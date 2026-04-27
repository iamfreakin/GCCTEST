#include "FireGoblin.h"

FireGoblin::FireGoblin(const string& name, int str, int dex, int vit, int eng, int expReward, int lv)
    : Monster(name, str, dex, vit, eng, expReward, lv) {}

int FireGoblin::Attack() const
{
    return (int)(attackDamage * 1.5f);
}
