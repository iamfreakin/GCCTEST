#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <iomanip>
#include <deque>
#include <windows.h>

using namespace std;

// 몬스터 데이터 구조체
struct MonsterData {
    string name = "";
    int hp = 0;
    int maxHp = 0;
    int atk = 0;      // [추가] 몬스터 공격력
    bool active = false;
};

// 게임 데이터 구조체
struct GameData {
    string name = "Unknown";   // 초기값 부여
    string job = "None";      // 초기값 부여
    int level = 1;
    int maxHp = 100;
    int hp = 100;             // 초기값 필수!
    int mp = 0;               // 초기값 필수!
    float atkSpd = 1.0f;      // 초기값 필수!
    float atkDmg = 10.0f;     // 초기값 필수!
    int str = 0;              // 초기값 필수!
    int dex = 0;              // 초기값 필수!
    int vit = 0;              // 초기값 필수!
    int eng = 0;              // 초기값 필수!
    bool hardcore = false;    // 초기값 필수!
    int inventory[4] = { 0, 0, 0, 0 };
    deque<string> logs;
    MonsterData currentMonster;
};

// --- [ UI 제어 유틸리티 ] ---
void SetColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void HideCursor() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

void MoveCursorToTop() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = { 0, 0 };
    SetConsoleCursorPosition(hConsole, coord);
}

void AddLog(GameData& data, string message) {
    data.logs.push_back(message);
    if (data.logs.size() > 6) data.logs.pop_front();
}

// --- [ 3분할 렌더링 함수 ] ---
void RenderScene(const GameData& data) {
    MoveCursorToTop();
    SetColor(8); // 어두운 회색 (테두리)

    cout << "┌──────────────────────────────┬─────────────────────────────────────────────┬───────────────────────────────────┐" << endl;
    cout << "│      [ ENEMY STATUS ]        │            [ GAME PROGRESS LOG ]            │        [ CHARACTER STATUS ]       │" << endl;
    cout << "├──────────────────────────────┼─────────────────────────────────────────────┼───────────────────────────────────┤" << endl;

    string invStr = "  INV   : G:" + to_string(data.inventory[0]) + " P:" + to_string(data.inventory[1]) +
        " W:" + to_string(data.inventory[2]) + " A:" + to_string(data.inventory[3]);

    for (int i = 0; i < 7; i++) {
        SetColor(8); cout << "│";

        // 1. 좌측 영역: 몬스터 (30칸)
        if (data.currentMonster.active) {
            if (i == 1) {
                SetColor(12); cout << left << setw(30) << ("  NAME : " + data.currentMonster.name);
            }
            else if (i == 2) {
                SetColor(15); cout << "  HP   : ";
                SetColor(12);
                string mBar = "[";
                int mSeg = (data.currentMonster.maxHp > 0) ? (data.currentMonster.hp * 10) / data.currentMonster.maxHp : 0;
                for (int j = 0; j < 10; j++) mBar += (j < mSeg) ? "#" : "-";
                mBar += "] " + to_string(data.currentMonster.hp);
                cout << left << setw(21) << mBar;
            }
            else if (i == 3) {
                SetColor(12); cout << left << setw(30) << ("  ATK  : " + to_string(data.currentMonster.atk));
            }
            else cout << setw(30) << "";
        }
        else cout << setw(30) << "";

        SetColor(8); cout << "│";

        // 2. 중앙 영역: 로그 (45칸)
        string dLog = (i < data.logs.size()) ? " > " + data.logs[i] : "";
        if (dLog.find("damage") != string::npos || dLog.find("lost") != string::npos) SetColor(12);
        else if (dLog.find("Victory") != string::npos || dLog.find("Found") != string::npos) SetColor(10);
        else if (dLog.find("Welcome") != string::npos) SetColor(11);
        else SetColor(15);
        cout << left << setw(45) << dLog;

        SetColor(8); cout << "│";

        // 3. 우측 영역: 캐릭터 (35칸)
        SetColor(15);
        if (i == 0) cout << left << setw(35) << ("  NAME  : " + data.name);
        else if (i == 1) cout << left << setw(35) << ("  CLASS : " + data.job + " (Lv." + to_string(data.level) + ")");
        else if (i == 2) {
            cout << "  HP    : ";
            float hpP = (float)data.hp / data.maxHp;
            if (hpP > 0.7) SetColor(10); else if (hpP > 0.3) SetColor(14); else SetColor(12);
            string hBar = "[";
            int hSeg = (data.hp * 10) / data.maxHp;
            for (int j = 0; j < 10; j++) hBar += (j < hSeg) ? "#" : "-";
            hBar += "] " + to_string(data.hp);
            cout << left << setw(25) << hBar;
        }
        else if (i == 3) cout << left << setw(35) << ("  ATK   : " + to_string((int)data.atkDmg) + " / SPD: " + to_string(data.atkSpd).substr(0, 3));
        else if (i == 4) cout << left << setw(35) << ("  STATS : S:" + to_string(data.str) + " D:" + to_string(data.dex) + " V:" + to_string(data.vit));
        else if (i == 5) { SetColor(14); cout << left << setw(35) << invStr; }
        else cout << left << setw(35) << ("  MODE  : " + string(data.hardcore ? "HARDCORE" : "STANDARD"));

        SetColor(8); cout << "│" << endl;
    }
    cout << "└──────────────────────────────┴─────────────────────────────────────────────┴───────────────────────────────────┘" << endl;

    SetColor(15);
    cout << "                                                                                                    " << endl;
    cout << "                                                                                                    " << endl;
    COORD coord = { 0, 12 };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// --- [ 게임 로직 함수들 ] ---

void LoadingEffect(const GameData& data, string message) {
    for (int i = 0; i < 3; i++) {
        RenderScene(data);
        SetColor(14);
        cout << " [System] " << message;
        for (int j = 0; j <= i; j++) cout << ".";
        Sleep(300);
    }
}

void CreateCharacter(GameData& data) {
    int choice; char hc;
    system("cls");
    SetColor(11);
    cout << "┌────────────────────────────────────────────────────────────┐" << endl;
    cout << "│                [ CHARACTER CREATION ]                      │" << endl;
    cout << "└────────────────────────────────────────────────────────────┘" << endl;
    SetColor(15);
    cout << " > Input your name : "; cin >> data.name;
    cout << "\n > (1)Warrior (2)Rogue (3)Sorcerer / Choice: "; cin >> choice;

    switch (choice) {
    case 1: data.job = "Warrior"; data.str += 10; break;
    case 2: data.job = "Rogue"; data.dex += 10; break;
    case 3: data.job = "Sorcerer"; data.eng += 10; break;
    default: data.job = "Adventurer"; break;
    }

    cout << " > Enable Hardcore Mode? (1)Yes (0)No : "; cin >> hc;
    data.hardcore = (hc == '1');

    data.hp = data.vit; data.maxHp = data.vit;
    data.atkDmg = data.str * 0.25f; data.atkSpd = data.dex / 10.0f;

    AddLog(data, "Welcome, " + data.name + ". Your journey begins.");
    LoadingEffect(data, "Generating Character Data");
}

bool StartBattle(GameData& data) {
    // [랜덤 몬스터 생성 로직]
    string names[] = { "Slime", "Goblin", "Orc", "Skeleton", "Wild Wolf" };
    data.currentMonster.name = names[rand() % 5];

    // 플레이어가 100 HP일 때 적절한 난이도 (30~70 HP, 7~15 ATK)
    data.currentMonster.maxHp = rand() % 41 + 30;
    data.currentMonster.hp = data.currentMonster.maxHp;
    data.currentMonster.atk = rand() % 9 + 7;
    data.currentMonster.active = true;

    AddLog(data, "A " + data.currentMonster.name + " appeared from the shadows!");
    int act;

    while (data.currentMonster.hp > 0 && data.hp > 0) {
        RenderScene(data);
        SetColor(11); cout << " [Action] 1.Attack : "; cin >> act;

        if (act == 1) {
            int d = (int)data.atkDmg;
            data.currentMonster.hp -= d;
            AddLog(data, "You hit " + data.currentMonster.name + "! (-" + to_string(d) + " damage)");
            RenderScene(data);
            Sleep(300);

            if (data.currentMonster.hp > 0) {
                // 몬스터의 실제 atk 스탯을 사용함
                int mDmg = data.currentMonster.atk;
                data.hp -= mDmg;
                AddLog(data, data.currentMonster.name + " attacks! You lost " + to_string(mDmg) + " HP.");
                RenderScene(data);
                Sleep(400);
            }
        }
    }

    if (data.hp > 0) {
        AddLog(data, "Victory! " + data.currentMonster.name + " slain.");
        data.currentMonster.active = false;
        RenderScene(data);
        return true;
    }
    return false;
}

void Looting(GameData& data) {
    LoadingEffect(data, "Searching the remains");
    for (int i = 0; i < 3; i++) {
        int r = rand() % 4;
        string itemName = "";
        switch (r) {
        case 0: itemName = "Gold"; data.inventory[0] += (rand() % 50 + 10); break;
        case 1: itemName = "Potion"; data.inventory[1] += 1; break;
        case 2: itemName = "Old Sword"; data.inventory[2] += 1; break;
        case 3: itemName = "Armor Plate"; data.inventory[3] += 1; break;
        }
        AddLog(data, "Found: [" + itemName + "]");
        RenderScene(data);
        Sleep(500);
    }
    cout << " Inventory updated! Press any key to continue... ";
    system("pause > nul");
}

//int main() {
//    HideCursor();
//    srand((unsigned int)time(NULL));
//
//    GameData player;
//    player.str = 50; player.dex = 50; player.vit = 100; player.eng = 50;
//    player.currentMonster.active = false;
//
//    CreateCharacter(player);
//
//    // 루프를 돌려 여러 번 전투할 수 있게 확장 가능
//    if (StartBattle(player)) {
//        Looting(player);
//    }
//    else {
//        SetColor(12);
//        AddLog(player, "You died...");
//        RenderScene(player);
//        cout << " --- GAME OVER ---" << endl;
//    }
//
//    SetColor(15);
//    return 0;
//}
                                     

/*
// Call By Value vs Call By Address (Reference) 예제
// 실습 확인용 함수 PreviewCriticalDamage()
// PreviewLevelUp_Address(), PreviewLevelUp_Reference() 를 구현하고 main()에서 호출하여 결과 확인
*/

void PreviewCriticalDamage(GameData data) {
    // Call By Value 예제
    data.atkDmg *= 2;
    cout << "Preview Critical Damage (Call By Value): " << data.atkDmg << '\n';
}

void PreviewLevelUp_Address(GameData* data) {
    // Call By Value 예제
    data->level += 1;
	cout << "Preview Level Up (Call By Address): " << data->level << '\n';
}

void PreviewLevelUp_Reference(GameData& data) {
    // Call By Value 예제
    data.level += 1;
    cout << "Preview Level Up (Call By Reference): " << data.level << '\n';
}

int main()
{
    GameData player;

    cout << "Damage : " << player.atkDmg << '\n';
    PreviewCriticalDamage(player);
    cout << "Damage : " << player.atkDmg << '\n';
    cout << "===========================" << '\n';
	cout << "Level : " << player.level << '\n';
	PreviewLevelUp_Address(&player);
    cout << "Level : " << player.level << '\n';
    cout << "===========================" << '\n';
    cout << "Level : " << player.level << '\n';
    PreviewLevelUp_Reference(player);
    cout << "Level : " << player.level << '\n';
}