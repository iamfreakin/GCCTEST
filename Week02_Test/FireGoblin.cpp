#include "FireGoblin.h"

FireGoblin::FireGoblin(std::string n, int str, int dex, int vit, int eng, int lv) : Monster()
{
    
}

int FireGoblin::Attack() const
{
    return (int)attackDamage * 1.5;
}
