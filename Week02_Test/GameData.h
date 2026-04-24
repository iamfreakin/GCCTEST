#pragma once
#include <deque>

#include "Player.h"
#include "Monster.h"

using std::string;
using std::deque;

class GameData {
private:
    Player currentPlayer;
    Monster currentMonster;
    deque<string> logs;
    bool hardcore;
    
public:
    GameData() : hardcore(false) {}
    
    void AddLog(const string& message);

    void SetHardcore(bool val) { hardcore = val; }
    bool IsHardcore() const { return hardcore; }

    Player& GetPlayer() { return currentPlayer; }
    const Player& GetPlayer() const { return currentPlayer; }

    Monster& GetMonster() { return currentMonster; }
    const Monster& GetMonster() const { return currentMonster; }

    const deque<string>& GetLogs() const { return logs; }
};