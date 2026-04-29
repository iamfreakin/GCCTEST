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

unique_ptr<Item> Monster::Drop() const
{
    // 50% 확률로 아이템이 드롭 되도록, 아이템 종류는 랜덤
    if (rand() % 2 == 0) return nullptr; // 일반 몬스터는 절반 확률로 드롭 없음
    
    int roll = rand() % 3; // 0, 1, 2 중
    if (roll == 0) return make_unique<Item>("Short Sword", ItemType::Weapon);
    else if (roll == 1) return make_unique<Item>("leather Armor", ItemType::Armor);
    else return make_unique<Item>("Healing Potion", ItemType::Consumable);
}
