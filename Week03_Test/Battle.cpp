#include "Battle.h"
#include <iostream>
#include <cstdlib>
#include <iomanip>

#include "Mercenary.h"

Battle::Battle(Player& player, Monster& monster, shared_ptr<Mercenary> mercenary)
    : player(player), monster(monster), mercenary(mercenary), combatMessage("[System] Battle Started!") {}

bool Battle::Run()
{
    int action;

    while (monster.isAlive() && player.isAlive()) {
        int dGoblinHp = monster.GetHp();
        int dPlayerHp = player.GetHp();

        int gBarCnt = (dGoblinHp * 20) / monster.GetMaxHp();
        int pBarCnt = (dPlayerHp * 20) / player.GetMaxHp();

        string gBar = string(gBarCnt, '=') + string(20 - gBarCnt, '-');
        string pBar = string(pBarCnt, '=') + string(20 - pBarCnt, '-');

        // 체력 게이지와 이전 턴의 결과를 함께 출력
        cout << "==================================================\n";
        cout << "|| GOBLIN [" << gBar << "] " << left << setw(12) << dGoblinHp << "||\n";
        cout << "|| PLAYER [" << pBar << "] " << left << setw(12) << dPlayerHp << "||\n";
        cout << "==================================================\n";
        cout << combatMessage << "\n";
        cout << "--------------------------------------------------\n";
        cout << ">> 1. Attack\n>> 2. Bash Attack\n Select Action : ";
        cin >> action;

        // 행동 처리 및 결과 메시지 갱신
        if (action == 1) {
            monster.TakeDamage(player.Attack()); // 객체 스스로가 데미지를 처리하고 있음
            combatMessage = "=>" + player.GetAttackMessage() + " You attacked the Goblin! (Dmg: " + to_string(player.Attack()) + ")";

            if (mercenary && monster.isAlive())
            {
                int mercDmg =  mercenary->Attack();
                monster.TakeDamage(mercDmg);
                combatMessage += "\n=> [" + mercenary->name + "] attacked! (Dmg: " + to_string(mercDmg) + ")";
            }
            
            if (monster.isAlive()) {
                player.TakeDamage(monster.Attack());
                combatMessage += "\n=>" + monster.GetAttackMessage() + " The " 
                + monster.GetName() + " attacked you! (Dmg: " + to_string(monster.Attack()) + ")";
            }
        }
        else if (action == 2) {
            monster.TakeDamage(player.CriticalAttack()); // 2배 데미지 받음
            combatMessage = "=>" + player.GetAttackMessage() + " You attacked the Goblin! (Dmg: " + to_string(player.Attack()) + ")";
            
            if (mercenary && monster.isAlive())
            {
                int mercDmg = mercenary->Attack();
                monster.TakeDamage(mercDmg);
                combatMessage += "\n=> [" + mercenary->name + "] attacked! (Dmg: " + to_string(mercDmg) + ")"; 
            }
            
            if (monster.isAlive()) {
                player.TakeDamage(monster.Attack());
                combatMessage += "\n=>" + monster.GetAttackMessage() + " The " 
                + monster.GetName() + " attacked you! (Dmg: " + to_string(monster.Attack()) + ")";
            }
        }
        else {
            cin.clear();
            cin.ignore(100, '\n');
            player.TakeDamage(monster.Attack());
            combatMessage = "=> Invalid action! You stumbled.\n=> The Goblin attacked you! (Dmg: 30)";
        }

        // 대기 없이 즉시 화면을 지우고 루프 처음으로 돌아가 변경된 체력바 출력
        system("cls");
    }
    
    return player.isAlive();
}