#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <iomanip>
#include <deque>
#include <windows.h>

using namespace std;

struct GameData {
    string name;
    string job;
    int level = 1;
    int maxHp = 100, hp, mp;
    float atkSpd, atkDmg;
    int str, dex, vit, eng;
    bool hardcore;
    deque<string> logs;
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
    if (data.logs.size() > 6) {
        data.logs.pop_front();
    }
}

// --- [ 핵심 렌더링 함수 ] ---

void RenderScene(const GameData& data) {
    MoveCursorToTop();

    SetColor(8); // 어두운 회색 (테두리)
    cout << "┌────────────────────────────────────────────────────────────┬────────────────────────────────────┐" << endl;
    cout << "│                    ";
    SetColor(15); cout << "[ GAME PROGRESS LOG ]";
    SetColor(8); cout << "                   │         ";
    SetColor(15); cout << "[ CHARACTER STATUS ]";
    SetColor(8); cout << "       │" << endl;
    cout << "├────────────────────────────────────────────────────────────┼────────────────────────────────────┤" << endl;

    // 상태창 데이터 준비
    string status[6];
    status[0] = "  NAME  : " + data.name;
    status[1] = "  CLASS : " + data.job + " (Lv." + to_string(data.level) + ")";
    status[2] = "  HP    : "; // HP는 아래 루프에서 따로 처리 (색상 때문)
    status[3] = "  ATK   : " + to_string((int)data.atkDmg) + " / SPD: " + to_string(data.atkSpd).substr(0, 3);
    status[4] = "  STATS : S:" + to_string(data.str) + " D:" + to_string(data.dex) + " V:" + to_string(data.vit);
    status[5] = "  MODE  : " + string(data.hardcore ? "HARDCORE" : "STANDARD");

    for (int i = 0; i < 6; i++) {
        SetColor(8); cout << "│ ";

        // [로그 색상 강조]
        string displayLog = (i < data.logs.size()) ? " > " + data.logs[i] : "";
        if (displayLog.find("damage") != string::npos || displayLog.find("lost") != string::npos) SetColor(12); // 빨강
        else if (displayLog.find("Victory") != string::npos || displayLog.find("Found") != string::npos) SetColor(10); // 초록
        else if (displayLog.find("Welcome") != string::npos) SetColor(11); // 하늘
        else SetColor(15); // 기본 흰색

        cout << left << setw(59) << displayLog;

        SetColor(8); cout << "│";

        // [상태창 및 HP바 색상 처리]
        if (i == 2) { // HP 출력 줄
            SetColor(15); cout << "  HP    : ";

            float hpPercent = (float)data.hp / data.maxHp;
            if (hpPercent > 0.7) SetColor(10);      // 70% 이상 초록
            else if (hpPercent > 0.3) SetColor(14); // 30% 이상 노랑
            else SetColor(12);                     // 30% 미만 빨강

            string hpBar = "[";
            int hpSegments = data.hp / 10;
            if (hpSegments < 0) hpSegments = 0;
            for (int j = 0; j < 10; j++) hpBar += (j < hpSegments) ? "#" : "-";
            hpBar += "] " + to_string(data.hp);
            cout << left << setw(26) << hpBar;
        }
        else {
            SetColor(15); cout << left << setw(36) << status[i];
        }

        SetColor(8); cout << "│" << endl;
    }

    SetColor(8); cout << "└────────────────────────────────────────────────────────────┴────────────────────────────────────┘" << endl;

    // 하단 클리닝
    SetColor(15);
    cout << "                                                                                                    " << endl;
    cout << "                                                                                                    " << endl;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = { 0, 11 };
    SetConsoleCursorPosition(hConsole, coord);
}

// --- [ 게임 로직 ] ---

void LoadingEffect(const GameData& data, string message) {
    for (int i = 0; i < 3; i++) {
        RenderScene(data);
        SetColor(14);
        cout << " [System] " << message;
        for (int j = 0; j <= i; j++) cout << ".";
        Sleep(250);
    }
}

void CreateCharacter(GameData& data) {
    int classChoice;
    char hardcoreChoice;

    system("cls");
    SetColor(11);
    cout << "┌────────────────────────────────────────────────────────────┐" << endl;
    cout << "│                [ CHARACTER CREATION ]                      │" << endl;
    cout << "└────────────────────────────────────────────────────────────┘" << endl;
    SetColor(15);
    cout << " > Input your name : "; cin >> data.name;
    cout << "\n > (1)Warrior (2)Rogue (3)Sorcerer / Choice: "; cin >> classChoice;

    switch (classChoice) {
    case 1: data.job = "Warrior"; break;
    case 2: data.job = "Rogue"; break;
    case 3: data.job = "Sorcerer"; break;
    default: data.job = "Unknown"; break;
    }

    cout << " > Enable Hardcore? (1)Yes (0)No : "; cin >> hardcoreChoice;
    data.hardcore = (hardcoreChoice == '1');

    AddLog(data, "Welcome, " + data.name + ". Your journey begins.");
    LoadingEffect(data, "Generating Character Data");
}

bool StartBattle(GameData& data) {
    int goblinHp = 40;
    int action;
    AddLog(data, "A wild Goblin appeared!");

    while (goblinHp > 0 && data.hp > 0) {
        RenderScene(data);
        SetColor(11);
        cout << " [Action] 1.Attack : ";
        cin >> action;

        if (action == 1) {
            // 플레이어 공격 연출
            int damage = (int)data.atkDmg;
            goblinHp -= damage;
            AddLog(data, "You dealt " + to_string(damage) + " damage to Goblin.");
            RenderScene(data);
            Sleep(300);

            if (goblinHp > 0) {
                // 고블린 반격 연출
                data.hp -= 25;
                AddLog(data, "Goblin counter-attacks! You lost 25 HP.");
                RenderScene(data);
                // 피격 시 화면을 잠깐 빨간색으로 "반짝"하게 하고 싶다면 여기서 색을 바꿨다 풀 수 있습니다.
                Sleep(400);
            }
        }
    }
    return data.hp > 0;
}

int main() {
    HideCursor();
    srand((unsigned int)time(NULL));

    GameData player;
    player.str = 60; player.dex = 50; player.vit = 100; player.eng = 50;
    player.hp = player.vit;
    player.maxHp = player.vit;
    player.atkDmg = player.str * 0.25f;
    player.atkSpd = player.dex / 10.0f;

    CreateCharacter(player);

    if (StartBattle(player)) {
        SetColor(10);
        AddLog(player, "Victory! The Goblin has been defeated.");
        RenderScene(player);
        cout << " You found a rare gem in the dust!" << endl;
    }
    else {
        SetColor(12);
        AddLog(player, "You lost too much blood... The world fades.");
        RenderScene(player);
        cout << " --- GAME OVER ---" << endl;
    }

    SetColor(15);
    system("pause > nul");
    return 0;
}