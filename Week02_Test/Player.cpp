#include "Player.h"

Player::Player() : name("Unknown"), job("None"), level(1), hp(100), maxHp(100),
               str(0), dex(0), vit(0), eng(0), atkDmg(10.0f), atkSpd(1.0f) {
    std::fill(std::begin(inventory), std::end(inventory), 0);
}

void Player::Initialize(string n, int jobChoice) {
    name = n;
    switch (jobChoice) {
    case 1: job = "Warrior";  str = 15; dex = 5;  vit = 15; break;
    case 2: job = "Rogue";    str = 8;  dex = 18; vit = 10; break;
    case 3: job = "Sorcerer"; str = 5;  dex = 10; vit = 8;  eng = 20; break;
    default: job = "Adventurer"; str = 10; dex = 10; vit = 10; break;
    }
    maxHp = vit * 10;
    hp = maxHp;
    atkDmg = (float)str * 1.5f;
    atkSpd = 1.0f + (dex * 0.05f);
}

void Player::TakeDamage(int dmg) {
    hp = std::max(0, hp - dmg);
}

void Player::LevelUp() {
    level++;
    maxHp += 20;
    hp = maxHp;
}

void Player::AddItem(int type, int amount) {
    if (type >= 0 && type < 4) inventory[type] += amount;
}