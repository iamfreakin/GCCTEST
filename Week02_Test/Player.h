#pragma once
#include <vector>
#include "Character.h"
#include "Item.h"

class Player : public Character {
private:
    // Player만이 가지는 고유 데이터
    std::string job;
    std::vector<Item> inventory; // vector사용
    int exp;
    int expToNextLevel;

public:
    Player();

    // Player 고유 기능
    void Initialize(std::string n, int jobChoice);
    void LevelUp();
    void GainExp(int amount);
    
    // 아이템 관련 함수 변경
    void AddItem(const Item& item);
    void UseItem(int index);
    
    // Player 고용 Getter
    std::string GetJobName() const { return job; }
    const std::vector<Item> GetInvItem(int idx) const { return inventory; }
    int GetExp() const { return exp; }
    int GetExpToNextLevel() const { return expToNextLevel; }
    
};