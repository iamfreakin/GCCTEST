#include "Monster.h"
#include <iostream>

Monster::Monster(const string& name, int str, int dex, int vit, int eng, int expReward, int lv) 
: Character(str, dex, vit, eng, lv), name(name), expReward(expReward)
{
    cout << "[몬스터 생성]" << name << "\n";
}

Monster::~Monster()
{
    cout << "[몬스터 소멸]" << name << "\n";
}