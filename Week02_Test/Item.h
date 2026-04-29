#pragma once
#include <string>

// 아이템 종류 구분
enum class ItemType {
    None,
    Consumable, // 소모품 (포션 등)
    Weapon,     // 무기
    Armor,      // 방어구
    Gold        // 재화
};

class Item {
private:
    std::string name;
    ItemType type;
    int value;      // 회복량 또는 공격력/방어력 수치

public:0, 
    Item();
    Item(std::string n, ItemType t, int v, int g);

    // Getters
    std::string GetName() const { return name; }
    ItemType GetType() const { return type; }
    int GetValue() const { return value; }
};