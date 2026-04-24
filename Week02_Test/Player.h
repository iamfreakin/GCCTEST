#pragma once
#include <string>

using std::string;

class Player {
private:
    string name, job;
    int level, hp, maxHp;
    int str, dex, vit, eng;
    float atkDmg, atkSpd;
    int inventory[4]; 

public:
    Player();

    void Initialize(string n, int jobChoice);
    void TakeDamage(int dmg);
    void LevelUp();
    void AddItem(int type, int amount);

    string GetName() const { return name; }
    string GetJobName() const { return job; }
    int GetLevel() const { return level; }
    int GetHp() const { return hp; }
    int GetMaxHp() const { return maxHp; }
    int GetStr() const { return str; }
    int GetDex() const { return dex; }
    int GetVit() const { return vit; }
    int GetInvItem(int idx) const { return inventory[idx]; }
    float GetAtkDmg() const { return atkDmg; }
    float GetAtkSpd() const { return atkSpd; }
    bool IsAlive() const { return hp > 0; }
};