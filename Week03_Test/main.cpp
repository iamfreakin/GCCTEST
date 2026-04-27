#include <iostream>
#include <string>
#include <cstdlib> 
#include <iomanip>
#include <vector>

#include "Barbarian.h"
#include "Battle.h"
#include "FireGoblin.h"
#include "Monster.h"
#include "Player.h"
#include "Sorceress.h"
using namespace std;

int main()
{
	string userName;
	string charactorClass;
	int classChoiceInput;
	char hardcoreInput;
	bool isHardcore = true;

	// 1. 캐릭터 생성 UI
	cout << "==========================================================================\n";
	cout << "      :::::::::  :::::::::::     :::     :::::::::  :::        :::::::: \n";
	cout << "     :+:    :+:     :+:         :+:     :+:    :+: :+:       :+:    :+: \n";
	cout << "    +:+    +:+     +:+        +:+ +:+   +:+    +:+ +:+       +:+    +:+  \n";
	cout << "   +#+    +:+     +#+       +#+  +:+  +#++:++#+  +#+       +#+    +:+   \n";
	cout << "  +#+    +#+     +#+      +#+#+#+#+# +#+    +#+ +#+       +#+    +#+    \n";
	cout << " #+#    #+#     #+#     #+#      #+# #+#    #+# #+#       #+#    #+#     \n";
	cout << "#########  ########### ###      ### #########  ##########  ########      \n";
	cout << "                                             ::::::::                   \n";
	cout << "                                           :+:    :+:                   \n";
	cout << "        M  U  D                                 +:+                     \n";
	cout << "                                            +#++:                       \n";
	cout << "       E D I T I O N                      +#+                           \n";
	cout << "                                        #+#                             \n";
	cout << "                                      ##########                        \n";
	cout << "==========================================================================\n";
	cout << ">> Input your name : ";
	cin >> userName;

	system("cls"); // 화면 지우기

	// 직업 선택 UI
	cout << "==================================================\n";
	cout << "||" << left << setw(46) << "               SELECT YOUR CLASS" << "||\n";
	cout << "--------------------------------------------------\n";
	cout << "|| 1. Amazon       2. Assassin     3. Barbarian ||\n";
	cout << "|| 4. Druid        5. Necromancer  6. Paladin   ||\n";
	cout << "|| 7. Sorceress    8. Warlock                   ||\n";
	cout << "==================================================\n";
	cout << ">> Input Class Number : ";
	cin >> classChoiceInput;

	switch (classChoiceInput) {
	case 1: charactorClass = "Amazon"; break;
	case 2: charactorClass = "Assassin"; break;
	case 3: charactorClass = "Barbarian"; break;
	case 4: charactorClass = "Druid"; break;
	case 5: charactorClass = "Necromancer"; break;
	case 6: charactorClass = "Paladin"; break;
	case 7: charactorClass = "Sorceress"; break;
	case 8: charactorClass = "Warlock"; break;
	default:
		charactorClass = "Unknown";
		cout << "[System] Invalid choice. Defaulting to Unknown.\n";
		break;
	}

	system("cls"); // 화면 지우기

	// Hardcore 모드 선택
	cout << ">> Enable Hardcore Mode? (1) Yes / (0) No : ";
	cin >> hardcoreInput;

	if (hardcoreInput == '1') {
		isHardcore = true;
		cout << "[System] Hardcore mode enabled. Death is permanent.\n";
	}
	else if (hardcoreInput == '0') {
		isHardcore = false;
		cout << "[System] Standard mode enabled.\n";
	}
	else {
		isHardcore = false;
		cout << "[System] Invalid input. Defaulting to Standard mode.\n";
	}

	cout << "\n";
	system("pause"); // 안내 메시지 확인을 위한 대기
	system("cls");   // 화면 지우기

	// Player 직업에따라 자식 클래스를 생성
	Player* playerPtr = nullptr;
	if (classChoiceInput == 3) playerPtr = new Barbarian(userName, isHardcore);
	else if (classChoiceInput == 7) playerPtr = new Sorceress(userName, isHardcore);
	else playerPtr = new Player(userName, charactorClass, isHardcore);
	Player& player = *playerPtr;
	
	// 2. 캐릭터 상태창 UI
	string hcText = isHardcore ? "ON" : "OFF";

	cout << "==================================================\n";
	cout << "||" << left << setw(46) << "               CHARACTER STATUS" << "||\n";
	cout << "==================================================\n";
	cout << "|| " << left << setw(13) << "NAME" << " || " << left << setw(27) << player.GetName() << " ||\n";
	cout << "|| " << left << setw(13) << "CLASS" << " || " << left << setw(27) << player.GetCharacterClass() << " ||\n";
	cout << "|| " << left << setw(13) << "LEVEL" << " || " << left << setw(27) << player.GetLevel() << " ||\n";
	cout << "==================================================\n";
	cout << "|| " << left << setw(13) << "HP" << " || " << left << setw(27) << player.GetMaxHp() << " ||\n";
	cout << "|| " << left << setw(13) << "MP" << " || " << left << setw(27) << player.GetMaxMp() << " ||\n";
	cout << "|| " << left << setw(13) << "DAMAGE" << " || " << left << setw(27) << player.GetAttackDamage() << " ||\n";
	cout << "|| " << left << setw(13) << "ATTACK SPD" << " || " << left << setw(27) << player.GetAttackSpeed() << " ||\n";
	cout << "|| " << left << setw(13) << "MOVING SPD" << " || " << left << setw(27) << player.GetMovingSpeed() << " ||\n";
	cout << "--------------------------------------------------\n";
	cout << "|| " << left << setw(13) << "STRENGTH" << " || " << left << setw(27) << player.GetStrength() << " ||\n";
	cout << "|| " << left << setw(13) << "DEXTERITY" << " || " << left << setw(27) << player.GetDexterity() << " ||\n";
	cout << "|| " << left << setw(13) << "VITALITY" << " || " << left << setw(27) << player.GetVitality() << " ||\n";
	cout << "|| " << left << setw(13) << "ENERGY" << " || " << left << setw(27) << player.GetEnergy() << " ||\n";
	cout << "==================================================\n";
	cout << "|| " << left << setw(13) << "HARDCORE" << " || " << left << setw(27) << player.GetIsHardcore() << " ||\n";
	cout << "|| " << left << setw(13) << "FIRE RES" << " || " << left << setw(27) << player.GetFireResist() << " ||\n";
	cout << "|| " << left << setw(13) << "LIGHT RES" << " || " << left << setw(27) << player.GetLightningResist() << " ||\n";
	cout << "|| " << left << setw(13) << "COLD RES" << " || " << left << setw(27) << player.GetColdResist() << " ||\n";
	cout << "|| " << left << setw(13) << "POISON RES" << " || " << left << setw(27) << player.GetPoisonResist() << " ||\n";
	cout << "==================================================\n\n";

	system("pause"); // 상태창 확인 대기
	system("cls");   // 화면 지우기

	// 3. 전투 시스템 UI
	int pendingExp = 0;
	vector<Monster*> GoblinMap = {
		new Monster("Goblin", 50, 0 ,15 ,0 ,50),
		new Monster("Goblin", 50, 0 ,15 ,0 ,50),
		new Monster("Goblin", 50, 0 ,15 ,0 ,50),
		new Monster("Goblin", 50, 0 ,15 ,0 ,50),
	};
	vector<Monster*> SkeletonMap = {
		new Monster("Skeleton", 60, 0 ,20 ,0 ,50),
		new Monster("Skeleton", 60, 0 ,20 ,0 ,50),
		new Monster("Skeleton", 60, 0 ,20 ,0 ,50),
		new Monster("Skeleton", 60, 0 ,20 ,0 ,50),
		
	};
	vector<Monster*> GhoulMap = {
		new Monster("Ghoul", 70, 0 ,35 ,0 ,120),
		new Monster("Ghoul", 70, 0 ,35 ,0 ,120),
		new Monster("Ghoul", 70, 0 ,35 ,0 ,120),
		new Monster("Ghoul", 70, 0 ,35 ,0 ,120),
	};
	
	vector<Monster*> tmp_monster;
	int DungeonChoiceInput;
	
	cout << "==================================================\n";
	cout << "||" << left << setw(46) << "               SELECT The Dungeon" << "||\n";
	cout << "--------------------------------------------------\n";
	cout << "||                                              ||\n";
	cout << "|| 1. GoblinMap    2. SkeletonMap  3. GhoulMap  ||\n";
	cout << "||                                              ||\n";
	cout << "==================================================\n";
	cout << ">> Input Dungeon Number : ";
	cin >> DungeonChoiceInput;
	
	switch (DungeonChoiceInput)
	{
		case 1: tmp_monster = GoblinMap; break;
		case 2: tmp_monster = SkeletonMap; break;
		case 3: tmp_monster = GhoulMap; break;
	}
	
	for (Monster* monster : tmp_monster)
	{
		if (!player.isAlive()) break;
		
		cout << "==================================================\n";
		cout << "||" << left << setw(46) << "           A " + monster->GetName() + "APPEARED!" << "||\n";
		cout << "==================================================\n\n";

		system("pause"); // 조우 메시지 확인용 1회 대기
		system("cls");

		// 전투기능 클래스 구현 이후 전투 생성과 실행
		Battle battle(player, *monster);
		battle.Run();
		
		// 전투 종료 후 결과 판정
		if (!player.isAlive()) {
			cout << "==================================================\n";
			cout << "||" << left << setw(46) << "                 YOU DIED..." << "||\n";
			cout << "==================================================\n";
		}
		else {
			cout << "==================================================\n";
			cout << "||" << left << setw(46) << "          YOU DEFEATED THE " + monster->GetName() + "!" << "||\n";
			cout << "==================================================\n";
		
			// 아이템 루팅
			player.Loot();

			// 레벨업
			player.GainExp(pendingExp);
			player.PrintLevel();
		}
	}
	
	// new로 생성한 몬스터 메모리 해제
	for (Monster* monster : GoblinMap)
	{
		delete monster;
	}
	for (Monster* monster : SkeletonMap)
	{
		delete monster;
	}
	for (Monster* monster : GhoulMap)
	{
		delete monster;
	}
	
	delete playerPtr;
	
	cout << "\n";
	system("pause"); // 프로그램 종료 전 결과창 유지
	return 0;
}