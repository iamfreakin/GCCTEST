#include "Player.h"
#include <iostream>
#include <string>
#include <iomanip>

Player::Player(const string& name, const string& characterClass, bool isHardcore)
    // 외부입력 값 세팅 초기화
    : Character(50, 50, 50, 50, 1),
    name(name), characterClass(characterClass), isHardcore(isHardcore),
    exp(0), expToNextLevel(100) // 단순 값 세팅 초기화
{
    maxHp = vitality * 2; // 계산이 필요한 값 세팅 초기화
    hp = maxHp;
    maxMp = (int)energy * 1.5f;
    mp = maxMp;
    attackDamage = strength * 0.2f;
    attackSpeed = dexterity / 10.0f;
    movingSpeed = dexterity / 30.0f;
}

Player::Player(const string& name, const string& characterClass, bool isHardcore,
    int str, int dex, int vit, int eng)
        : Character(str, dex, vit, eng, 1), exp(0), expToNextLevel(100) {}

void Player::LevelUp()
{
    level++;
}

void Player::PreviewCritical() const
{
    float preview = attackDamage * 2;
    cout << "크리티컬 예상 데미지: " << preview << "\n";
}

void Player::PrintLevel() const
{
    cout << "현재 레벨: " << level << "\n";
}

int Player::CriticalAttack() const
{
    return (int)(attackDamage * 2);
}

void Player::GainExp(int amount)
{
    exp += amount;
    if (exp >= expToNextLevel)
    {
        exp -= expToNextLevel;
        level++;
        expToNextLevel = level * 100;
        cout << "[레벨 업!] Level: " << level << "\n";
    }
}

void Player::AddItem(const Item& item)
{
    inventory.push_back(item);
}

void Player::Loot(int count)
{
    cout << "\n[System] Looting Items...\n";

    // count개 아이템을 vector에 추가
    for (int i = 0; i < count; i++)
    {
        // 랜덤 숫자 1개씩 인벤토리에 벡터에 넣음
        int r = rand() % 4 + 1;
        
        string itemname = "";
        switch (r)
        {
            case 0:
                itemname = "heal potion";
                AddItem(Item(itemname, ItemType::Consumable, 30, 20));
                break;
            case 1:
                itemname = "Weapon";
                AddItem(Item(itemname, ItemType::Weapon, 10, 50));
                break;
            case 2:
                itemname = "Armor";
                AddItem(Item(itemname, ItemType::Armor, 10, 40));
                break;
            case 3:
                itemname = "Gold";
                AddItem(Item(itemname, ItemType::Gold, 0, 50));
                break;
        }
        // 인벤토리 출력
        cout << "==================================================\n";
        cout << "||" << left << setw(46) << "          INVENTORY" << "||\n";
        cout << "==================================================\n";
        for (int j = 0; j < inventory.size(); j++)
        {
            cout << " > Slot " << j << " < [" << inventory[j].GetName() <<"]\n";
        }
    }
}