#pragma once
#include <string>
#include <vector>
#include "Character.h"
using namespace std;
#include "Item.h"

// Character 클래스를 상속 받은 Player 클래스
class Player : public Character
{
private:
	// Player 고유 정보
	string name;
	string characterClass;
	bool isHardcore;
	
	// 경험치
	int exp, expToNextLevel;
	
	// 인벤토리
	vector<Item> inventory;
	
public:
	// 생성자
	Player(const string& name, const string& characterClass, bool isHardcore);
	
protected:
	// 자식 클래스(바바리안, 소서리스 등)이 스탯을 직접 지정할때 사용되는 생성자
	Player(const string& name, const string& characterClass, bool isHardcore,
		int str, int dex, int vit, int eng);
	
public:
	string GetName() const { return name; }
	string GetCharacterClass() const { return characterClass; }
	bool GetIsHardcore() const { return isHardcore; }
	int GetExp() const { return exp; }
	int GetExpToNextLevel() const { return expToNextLevel; }
	
	// 기능(함수)
	int CriticalAttack() const;
	virtual string GetAttackMessage() const { return ""; }
	void LevelUp();
	void GainExp(int amount);
	void PreviewCritical() const;
	void PrintLevel() const;
	void AddItem(const Item& item);
	void Loot(int count = 3); // 빈 슬롯부터 count개의 아이템 획득 -> 인벤토리에 저장 + 출력
};