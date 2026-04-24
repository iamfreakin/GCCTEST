#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "GameData.h"
#include "GameRenderer.h"
#include "ConsoleSystem.h"

using std::string;
using std::cout;
using std::cin;
using std::endl;

class GameplayManager
{
public:
    static void CreateCharacter(GameData& data) {
        string n; int c; char hc;
        system("cls");
        ConsoleSystem::SetColor(11);
        cout << "┌────────────────────────────────────────────────────────────┐" << endl;
        cout << "│                [ CHARACTER CREATION ]                      │" << endl;
        cout << "└────────────────────────────────────────────────────────────┘" << endl;
        ConsoleSystem::SetColor(15);
        cout << " > Input your name : "; cin >> n;
        cout << "\n > (1)Warrior (2)Rogue (3)Sorcerer / Choice: "; cin >> c;
        cout << " > Enable Hardcore Mode? (1)Yes (0)No : "; cin >> hc;
        
        data.SetHardcore(hc == '1');
        data.GetPlayer().Initialize(n, c);
        data.AddLog("Welcome, " + data.GetPlayer().GetName() + ". Your journey begins.");
        GameRenderer::LoadingEffect(data, "Generating Character Data");
    }

    static bool StartBattle(GameData& data) {
        // 몬스터 이름과 보상 경험치 밸런싱
        string names[] = { "Slime", "Goblin", "Orc", "Skeleton", "Wild Wolf" };
        int monsterIdx = rand() % 5;
        
        // Spawn 시 네 번째 인자로 보상 경험치(XP) 전달
        // 예: 20 ~ 50 사이의 경험치 부여
        data.GetMonster().Spawn(names[monsterIdx], rand() % 41 + 30, rand() % 9 + 7, rand() % 31 + 20);

        data.AddLog("A " + data.GetMonster().GetName() + " appeared!");
    
        while (data.GetMonster().isAlive() && data.GetPlayer().isAlive()) {
            GameRenderer::RenderScene(data);
            
            // 이전 메시지 잔상 제거를 위한 클리어
            ConsoleSystem::ClearLine(0, 13, 100);
            
            int act;
            ConsoleSystem::SetColor(11); 
            cout << " [Action] 1.Attack  2.Critical : "; 
            cin >> act;

            string attackMsg = (act == 2) ? "Concentrating for Critical Hit" : "Swinging your weapon";
            GameRenderer::LoadingEffect(data, attackMsg, 0); // 전투 템포를 위해 빠른 로딩 적용
            
            float baseDmg = data.GetPlayer().GetAttackDamage();
            int finalDmg = (act == 2) ? static_cast<int>(baseDmg * 2) : static_cast<int>(baseDmg);
            
            data.GetMonster().TakeDamage(finalDmg);
            data.AddLog("You hit " + data.GetMonster().GetName() + "! (-" + std::to_string(finalDmg) + ")");
            GameRenderer::RenderScene(data); // 플레이어 공격 로그 먼저 보여주기
            Sleep(500);
            
            if (data.GetMonster().isAlive()) {
                int mDmg = data.GetMonster().Attack();
                data.GetPlayer().TakeDamage(mDmg);
                data.AddLog(data.GetMonster().GetName() + " attacks! You lost " + std::to_string(mDmg) + " HP.");
            }
            Sleep(400);
        }

        if (data.GetPlayer().isAlive()) {
            data.AddLog("Victory! " + data.GetMonster().GetName() + " slain.");
            
            // 승리 시 몬스터의 경험치 보상을 획득
            int rewardXp = data.GetMonster().GetExpReward();
            data.GetPlayer().GainExp(rewardXp); 
            
            data.GetMonster().SetActive(false);
            GameRenderer::RenderScene(data);
            return true;
        }
        return false;
    }

    static void Looting(GameData& data) {
        GameRenderer::LoadingEffect(data, "Searching the remains");
        for (int i = 0; i < 3; i++) {
            int r = rand() % 4;
            string itemName = "";
            switch (r) {
                case 0: itemName = "Gold"; data.GetPlayer().AddItem(0, (rand() % 50 + 10)); break;
                case 1: itemName = "Potion"; data.GetPlayer().AddItem(1, 1); break;
                case 2: itemName = "Old Sword"; data.GetPlayer().AddItem(2, 1); break;
                case 3: itemName = "Armor Plate"; data.GetPlayer().AddItem(3, 1); break;
            }
            data.AddLog("Found: [" + itemName + "]");
            GameRenderer::RenderScene(data);
            Sleep(500);
        }
        cout << " Inventory updated! Press any key to continue... ";
        system("pause > nul");
    }
};