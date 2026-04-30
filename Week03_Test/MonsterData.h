#pragma once
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

// Monster 클래스는 게임 로직(Attack, TakeDamage) + 상속구조를 담당함
// MonsterData는 DB용 데이터를 담당하도록 분리하기 위하여 정의
struct MonsterData
{
    int str, dex, vit, eng;
    int expReward;
    vector<int> dropPool;
};

unordered_map<string, MonsterData> createMonsterDB(); // 몬스터 DB 생성 함수
