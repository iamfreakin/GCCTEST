#pragma once
#include <iostream>
#include <ostream>

#include "ItemData.h"
#include "MonsterData.h"

class GameInstance
{
private:
    GameInstance()
    {
        std::cout << "[+GameInstance+]" << '\n';
        itemDB = createItemDB();
        monsterDB = createMonsterDB();
    }
    ~GameInstance()
    {
        std::cout << "[-GameInstance-]" << '\n';
    }
    GameInstance(const GameInstance&) = delete;
    GameInstance& operator=(const GameInstance&) = delete;
public:
    static GameInstance& GetGameInstance()
    {
        static GameInstance instance;
        return instance;
    }
    
    unordered_map<int, ItemData> itemDB;
    unordered_map<string, MonsterData> monsterDB;
};
