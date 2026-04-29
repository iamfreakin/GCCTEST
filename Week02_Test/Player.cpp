#include "Player.h"
#include <iostream>

// 생성자: Character 부모 생성자에 기본 인자 전달
Player::Player() : Character("Unknown", 10, 10, 10, 10, 1) {
    job = "None";
    exp = 0;
    expToNextLevel = 100;
}

void Player::Initialize(std::string n, int jobChoice) 
{
    name = n; // 부모의 protected 멤버
    
    // 직업별 스탯 설정 (부모 클래스의 변수명 사용)
    switch (jobChoice) 
    {
    case 1: job = "Warrior";  strength = 15; dexterity = 5;  vitality = 15; energy = 5;  break;
    case 2: job = "Rogue";    strength = 8;  dexterity = 18; vitality = 10; energy = 8;  break;
    case 3: job = "Sorcerer"; strength = 5;  dexterity = 10; vitality = 8;  energy = 20; break;
    default: job = "Adventurer"; strength = 10; dexterity = 10; vitality = 10; energy = 10; break;
    }

    // 파생 능력치 계산 로직 (Character 클래스의 변수들)
    maxHp = vitality * 10;
    hp = maxHp;
    maxMp = energy * 10;
    mp = maxMp;
    attackDamage = static_cast<float>(strength) * 1.5f;
    attackSpeed = 1.0f + (dexterity * 0.05f);
}

void Player::GainExp(int amount) 
{
    exp += amount;
    
    while (exp >= expToNextLevel) 
        {
        LevelUp();
    }
}

void Player::LevelUp() 
{
    level++;        // 부모의 변수
    maxHp += 20;
    hp = maxHp;
}

void Player::AddItem(const Item& item) 
{
    inventory.push_back(item);
}
void Player::UseItem(int index)
{
    if (index < 0 || index >= inventory.size()) return;
    
    Item& item = inventory[index];
    if (item.GetType() == ItemType::Consumable) {
        hp = std::min(maxHp, hp + item.GetValue()); // HP 회복
        inventory.erase(inventory.begin() + index);
    }
}