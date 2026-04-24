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
        cout << "┌──────────────────────────────┬─────────────────────────────────────────────┬───────────────────────────────────┐" << endl;
        cout << "│      [ ENEMY STATUS ]        │            [ GAME PROGRESS LOG ]            │        [ CHARACTER STATUS ]       │" << endl;
        cout << "├──────────────────────────────┼─────────────────────────────────────────────┼───────────────────────────────────┤" << endl;

        const Monster& m = data.GetMonster();
        const Player& p = data.GetPlayer();
        const auto& logs = data.GetLogs();

        for (int i = 0; i < 7; i++) 
        {
            ConsoleSystem::SetColor(8); cout << "│";

            // 1. 좌측 (Monster)
            if (m.IsActive()) {
                if (i == 1) { ConsoleSystem::SetColor(12); cout << left << setw(30) << ("  NAME : " + m.GetName()); }
                else if (i == 2) {
                    ConsoleSystem::SetColor(15); cout << "  HP   : ";
                    ConsoleSystem::SetColor(12);
                    string mBar = "[";
                    int mSeg = (m.GetMaxHp() > 0) ? (m.GetHp() * 10) / m.GetMaxHp() : 0;
                    for (int j = 0; j < 10; j++) mBar += (j < mSeg) ? "#" : "-";
                    mBar += "] " + to_string(m.GetHp());
                    cout << left << setw(21) << mBar;
                }
                else if (i == 3) { ConsoleSystem::SetColor(12); cout << left << setw(30) << ("  ATK  : " + to_string(m.GetAtk())); }
                else cout << setw(30) << "";
            } else cout << setw(30) << "";

            ConsoleSystem::SetColor(8); cout << "│";

            // 2. 중앙 (Logs)
            string dLog = (i < logs.size()) ? " > " + logs[i] : "";
            if (dLog.find("damage") != string::npos || dLog.find("lost") != string::npos) ConsoleSystem::SetColor(12);
            else if (dLog.find("Victory") != string::npos || dLog.find("Found") != string::npos) ConsoleSystem::SetColor(10);
            else ConsoleSystem::SetColor(15);
            cout << left << setw(45) << dLog;

            ConsoleSystem::SetColor(8); cout << "│";

            // 3. 우측 (Player)
            string invStr = "  INV   : G:" + to_string(p.GetInvItem(0)) + " P:" + to_string(p.GetInvItem(1)) +
                    " W:" + to_string(p.GetInvItem(2)) + " A:" + to_string(p.GetInvItem(3));
            ConsoleSystem::SetColor(15);
            if (i == 0) cout << left << setw(35) << ("  NAME  : " + p.GetName());
            else if (i == 1) cout << left << setw(35) << ("  CLASS : " + p.GetJobName() + " (Lv." + to_string(p.GetLevel()) + ")");
            else if (i == 2) {
                cout << "  HP    : ";
                float hpP = (float)p.GetHp() / p.GetMaxHp();
                if (hpP > 0.7) ConsoleSystem::SetColor(10); else if (hpP > 0.3) ConsoleSystem::SetColor(14); else ConsoleSystem::SetColor(12);
                string hBar = "[";
                int hSeg = (p.GetMaxHp() > 0) ? (p.GetHp() * 10) / p.GetMaxHp() : 0;
                for (int j = 0; j < 10; j++) hBar += (j < hSeg) ? "#" : "-";
                hBar += "] " + to_string(p.GetHp());
                cout << left << setw(25) << hBar;
            }
            else if (i == 3) { ConsoleSystem::SetColor(15); cout << left << setw(35) << ("  ATK   : " + to_string((int)p.GetAtkDmg()) + " / SPD: " + to_string(p.GetAtkSpd()).substr(0, 3)); }
            else if (i == 4) { ConsoleSystem::SetColor(15); cout << left << setw(35) << ("  STATS : S:" + to_string(p.GetStr()) + " D:" + to_string(p.GetDex()) + " V:" + to_string(p.GetVit())); }
            else if (i == 5) { ConsoleSystem::SetColor(14); cout << left << setw(35) << invStr; }
            else { ConsoleSystem::SetColor(15); cout << left << setw(35) << ("  MODE  : " + string(data.IsHardcore() ? "HARDCORE" : "STANDARD")); }

            ConsoleSystem::SetColor(8); cout << "│" << endl;
        }
        cout << "└──────────────────────────────┴─────────────────────────────────────────────┴───────────────────────────────────┘" << endl;
    }

    static void LoadingEffect(GameData& data, string message) 
        {
            for (int i = 0; i < 3; i++) {
                RenderScene(data);
                ConsoleSystem::SetColor(14);
                cout << " [System] " << message;
                for (int j = 0; j <= i; j++) cout << ".";
                Sleep(300);
            }
        }
};
