#pragma once
#include <string>

using std::string;


class Monster
{
private:
    string name;
    int hp;
    int maxHp;
    int attackDamage;
    bool active;
public:
    Monster();

    void Spawn(string n, int h, int a); 

    string GetName() const { return name; }
    int GetHp() const { return hp; }
    int GetMaxHp() const { return maxHp; }
    int GetAtk() const { return attackDamage; }
    bool IsActive() const { return active; }
    bool IsAlive() const { return hp > 0; }
    void SetActive(bool val) { active = val; }

    void TakeDamage(int damage);
};
