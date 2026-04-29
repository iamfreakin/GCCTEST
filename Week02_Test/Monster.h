#pragma once
#include "Character.h"

class Monster : public Character {
private:
    bool active;
    int expReward;

public:
    // 생성자: 부모 생성자를 호출하여 초기화
    Monster();
    
    void Spawn(std::string n, int h, int a, int xp); 

    // Monster 고유 Getter 및 Setter
    int GetExpReward() const { return expReward; }
    bool IsActive() const { return active; }
    void SetActive(bool val) { active = val; }
    
    
    virtual std::string GetAttackMessage() const { return ""; }
};