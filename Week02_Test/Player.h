#pragma once
#include "Character.h" // 부모 클래스 포함

class Player : public Character {
private:
    // Player만이 가지는 고유 데이터
    std::string job;
    int inventory[5]; // 이미지 설계에 맞춰 5칸으로 확장
    int exp;
    int expToNextLevel;

public:
    Player();

    // Player 고유 기능
    void Initialize(std::string n, int jobChoice);
    void LevelUp();
    void AddItem(int type, int amount);
    void GainExp(int amount);
    
    // Player 고용 Getter
    std::string GetJobName() const { return job; }
    int GetInvItem(int idx) const { return inventory[idx]; }
    int GetExp() const { return exp; }
    int GetExpToNextLevel() const { return expToNextLevel; }
    
};