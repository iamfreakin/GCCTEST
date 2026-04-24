#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>

#include "ConsoleSystem.h"
#include "Player.h"

using std::string;
using std::cout;
using std::endl;
using std::setw;
using std::to_string;
using std::left;

class GameRenderer
{
public:
   static void RenderScene(const GameData& data) 
{
    ConsoleSystem::MoveCursorToTop();
    ConsoleSystem::SetColor(8); 
    std::cout << "┌──────────────────────────────┬─────────────────────────────────────────────┬───────────────────────────────────┐" << std::endl;
    std::cout << "│      [ ENEMY STATUS ]        │            [ GAME PROGRESS LOG ]            │        [ CHARACTER STATUS ]       │" << std::endl;
    std::cout << "├──────────────────────────────┼─────────────────────────────────────────────┼───────────────────────────────────┤" << std::endl;

    const Monster& m = data.GetMonster();
    const Player& p = data.GetPlayer();
    const auto& logs = data.GetLogs();

    // 정보량이 많아졌으므로 루프를 9번으로 늘려 출력 공간 확보
    for (int i = 0; i < 9; i++) 
    {
        ConsoleSystem::SetColor(8); std::cout << "│";

        // 1. 좌측 (Monster Status)
        if (m.IsActive() && i < 4) {
            if (i == 1) { ConsoleSystem::SetColor(12); std::cout << std::left << std::setw(30) << ("  NAME : " + m.GetName()); }
            else if (i == 2) {
                ConsoleSystem::SetColor(15); std::cout << "  HP   : ";
                ConsoleSystem::SetColor(12);
                std::string mBar = "[";
                int mSeg = (m.GetMaxHp() > 0) ? (m.GetHp() * 10) / m.GetMaxHp() : 0;
                for (int j = 0; j < 10; j++) mBar += (j < mSeg) ? "#" : "-";
                mBar += "] " + std::to_string(m.GetHp());
                std::cout << std::left << std::setw(21) << mBar;
            }
            else if (i == 3) { ConsoleSystem::SetColor(12); std::cout << std::left << std::setw(30) << ("  ATK  : " + std::to_string((int)m.GetAttackDamage())); }
            else std::cout << std::setw(30) << "";
        } else std::cout << std::setw(30) << "";

        ConsoleSystem::SetColor(8); std::cout << "│";

        // 2. 중앙 (Game Logs)
        std::string dLog = (i < logs.size()) ? " > " + logs[i] : "";
        if (dLog.find("Victory") != std::string::npos || dLog.find("Level Up") != std::string::npos) ConsoleSystem::SetColor(10);
        else if (dLog.find("lost") != std::string::npos || dLog.find("died") != std::string::npos) ConsoleSystem::SetColor(12);
        else ConsoleSystem::SetColor(15);
        std::cout << std::left << std::setw(45) << dLog;

        ConsoleSystem::SetColor(8); std::cout << "│";

        // 3. 우측 (Player Status)
        ConsoleSystem::SetColor(15);
        if (i == 0) std::cout << std::left << std::setw(35) << ("  NAME  : " + p.GetName() + " (Lv." + std::to_string(p.GetLevel()) + ")");
        else if (i == 1) std::cout << std::left << std::setw(35) << ("  CLASS : " + p.GetJobName());
        else if (i == 2) { // HP Bar
            std::cout << "  HP    : ";
            float hpP = (float)p.GetHp() / p.GetMaxHp();
            if (hpP > 0.7) ConsoleSystem::SetColor(10); else if (hpP > 0.3) ConsoleSystem::SetColor(14); else ConsoleSystem::SetColor(12);
            std::string hBar = "[";
            int hSeg = (p.GetMaxHp() > 0) ? (p.GetHp() * 10) / p.GetMaxHp() : 0;
            for (int j = 0; j < 10; j++) hBar += (j < hSeg) ? "#" : "-";
            hBar += "] " + std::to_string(p.GetHp());
            std::cout << std::left << std::setw(25) << hBar;
        }
        else if (i == 3) { // MP Bar 추가
            ConsoleSystem::SetColor(15); std::cout << "  MP    : ";
            ConsoleSystem::SetColor(11); // Cyan
            std::string mpBar = "[";
            int mpSeg = (p.GetMaxMp() > 0) ? (p.GetMp() * 10) / p.GetMaxMp() : 0;
            for (int j = 0; j < 10; j++) mpBar += (j < mpSeg) ? "#" : "-";
            mpBar += "] " + std::to_string(p.GetMp());
            std::cout << std::left << std::setw(25) << mpBar;
        }
        else if (i == 4) { // XP Bar 추가
            ConsoleSystem::SetColor(15); std::cout << "  XP    : ";
            ConsoleSystem::SetColor(14); // Yellow
            std::string xBar = "[";
            int targetExp = p.GetExpToNextLevel();
            int xSeg = (targetExp > 0) ? (p.GetExp() * 10) / p.GetExpToNextLevel() : 0;
            for (int j = 0; j < 10; j++) xBar += (j < xSeg) ? "#" : "-";
            xBar += "] " + std::to_string(p.GetExp());
            std::cout << std::left << std::setw(25) << xBar;
        }
        else if (i == 5) { ConsoleSystem::SetColor(15); std::cout << std::left << std::setw(35) << ("  ATK   : " + std::to_string((int)p.GetAttackDamage()) + " / SPD: " + std::to_string(p.GetAttackSpeed()).substr(0, 4)); }
        else if (i == 6) { ConsoleSystem::SetColor(15); std::cout << std::left << std::setw(35) << ("  STATS : S:" + std::to_string(p.GetStrength()) + " D:" + std::to_string(p.GetDexterity()) + " V:" + std::to_string(p.GetVitality()) + " E:" + std::to_string(p.GetEnergy())); }
        else if (i == 7) { 
            ConsoleSystem::SetColor(14); // Gold
            std::string inv = "  INV   : G:" + std::to_string(p.GetInvItem(0)) + " P:" + std::to_string(p.GetInvItem(1)) + " W:" + std::to_string(p.GetInvItem(2)) + " A:" + std::to_string(p.GetInvItem(3));
            std::cout << std::left << std::setw(35) << inv; 
        }
        else { 
            ConsoleSystem::SetColor(8); 
            std::string mode = data.IsHardcore() ? "HARDCORE" : "STANDARD";
            std::cout << std::left << std::setw(35) << ("  MODE  : " + mode + " / Res: F" + std::to_string(p.GetFireResist())); 
        }

        ConsoleSystem::SetColor(8); std::cout << "│" << std::endl;
    }
    std::cout << "└──────────────────────────────┴─────────────────────────────────────────────┴───────────────────────────────────┘" << std::endl;
}

    static void LoadingEffect(GameData& data, string message, int time = 300) 
        {
            for (int i = 0; i < 3; i++) {
                RenderScene(data);
                ConsoleSystem::ClearLine(0, 13, 100);
                ConsoleSystem::SetColor(14);
                cout << " [System] " << message;
                for (int j = 0; j <= i; j++) cout << ".";
                Sleep(300);
            }
        }
};
