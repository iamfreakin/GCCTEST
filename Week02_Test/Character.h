#pragma once
#include <string>
#include <algorithm>

class Character {
protected:
    std::string name; // 기존 name 유지

    // 기본 능력치
    int strength, dexterity, vitality, energy;

    // 파생 능력치
    int level;
    int hp, maxHp;
    int mp, maxMp;
    float attackDamage;
    float attackSpeed;
    double movingSpeed;

    // 저항 능력치
    int fireResist, coldResist, lightningResist, poisonResist;

public:
    // 생성자: 모든 초기 스탯 설정
    Character(std::string n, int str, int dex, int vit, int eng, int lv);

    virtual ~Character() {} // 가상 소멸자

    // --- Getters ---
    std::string GetName() const { return name; }
    int GetStrength() const { return strength; }
    int GetDexterity() const { return dexterity; }
    int GetVitality() const { return vitality; }
    int GetEnergy() const { return energy; }
    int GetLevel() const { return level; }
    int GetHp() const { return hp; }
    int GetMaxHp() const { return maxHp; }
    int GetMp() const { return mp; }
    int GetMaxMp() const { return maxMp; }
    int GetFireResist() const { return fireResist; }
    int GetColdResist() const { return coldResist; }
    int GetLightningResist() const { return lightningResist; }
    int GetPoisonResist() const { return poisonResist; }
    float GetAttackDamage() const { return attackDamage; }
    float GetAttackSpeed() const { return attackSpeed; }
    double GetMovingSpeed() const { return movingSpeed; }
    bool isAlive() const { return hp > 0; }

    // --- 주요 기능 ---
    virtual void TakeDamage(int damage) {
        hp = std::max(0, hp - damage);
    }

    virtual int Attack() const { return (int)attackDamage; } // 기본 공격
};