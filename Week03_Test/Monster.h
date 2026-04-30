#pragma once
#include <memory>
#include "Character.h"
#include <string>
#include <vector>

#include "Item.h"
#include "MonsterData.h"
using namespace std;

class Monster : public Character
{
private:
    string name;
    int expReward;
    vector<int> dropPool; // 몬스터가 드롭 가능한 아이템 ID 목록
		
public:
    Monster(const string& name, const MonsterData& data, int lv = 1);
    
    string GetName() const { return name; }
    int GetExpReward() const { return expReward; }
    
    virtual string GetAttackMessage() const { return ""; }
    virtual int Drop() const; // 몬스터 처치 시 아이템이 드롭
};