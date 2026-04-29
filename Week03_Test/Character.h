#pragma once

class Character
{
protected:
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
	// Constructor
	Character(int str, int dex, int vit, int eng, int lv = 1);
	virtual ~Character() {} // 가상 소멸자: 자식 소멸자까지 안전하게 호출
	
	// Getters
	int GetStrength() const { return strength; }
	int GetDexterity() const { return dexterity; }
	int GetVitality() const { return vitality; }
	int GetEnergy() const { return energy; }
	int GetLevel() const { return level; }
	int GetHp() const { return hp; }
	int GetMaxHp() const { return maxHp; }
	int GetMaxMp() const { return maxMp; }
	int GetMp() const { return mp; }
	int GetFireResist() const { return fireResist; }
	int GetColdResist() const { return coldResist; }
	int GetLightningResist() const { return lightningResist; }
	int GetPoisonResist() const { return poisonResist; }
	float GetAttackDamage() const { return attackDamage; }
	float GetAttackSpeed() const { return attackSpeed; }
	float GetMovingSpeed() const { return movingSpeed; }
	bool isAlive() const { return hp > 0; }

	void TakeDamage(int damage);
	virtual int Attack() const;
};
