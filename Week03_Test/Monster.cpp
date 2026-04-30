#include "Monster.h"
#include <iostream>

Monster::Monster(const string& name, int str, int dex, int vit, int eng, 
    int expReward, int lv, vector<int> dropPool) 
: Character(str, dex, vit, eng, lv), name(name), expReward(expReward), dropPool(dropPool)
{}


int Monster::Drop() const
{
    // 50% 확률로 아이템이 드롭 되도록, 아이템 종류는 랜덤
    if (dropPool.empty() || rand() % 2 == 0) return -1; // 풀이 없거나 50% 확률로 드롭 아이템 없음
    return dropPool[rand() % dropPool.size()]; // 드롭 풀에서 랜덤으로 선택
}
