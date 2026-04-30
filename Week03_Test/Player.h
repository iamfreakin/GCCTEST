#pragma once
#include <memory>
#include <string>
#include <vector>
#include "Character.h"
#include "Item.h"
using namespace std;
class Mercenary; // 전방선언

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
	// 소멸자
	virtual ~Player();
	
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
	
	// 플레이어->용병 참조
	shared_ptr<Mercenary> companion;
	
	// 기능(함수)
	int CriticalAttack() const;
	virtual string GetAttackMessage() const { return ""; }
	void LevelUp();
	void GainExp(int amount);
	void PreviewCritical() const;
	void PrintLevel() const;
	void Loot(Item item); // 소권 이전을 통한 아이템 획득유
	bool UseItem(const string& itemName); // 아이템 사용 -> 인벤토리에서 제거 (없으면 false)
	
	void SortInventory();
	void PrintInventory() const; // 인벤토리 전체 출력
};