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
    bool active = false;
};

// 게임 데이터 구조체
struct GameData {
    string name;
    string job;
    int level = 1;
    int maxHp = 100, hp, mp;
    float atkSpd, atkDmg;
    int str, dex, vit, eng;
    bool hardcore;
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

    for (int i = 0; i < 6; i++) {
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
        else cout << left << setw(35) << ("  MODE  : " + string(data.hardcore ? "HARDCORE" : "STANDARD"));

        SetColor(8); cout << "│" << endl;
    }
    cout << "└──────────────────────────────┴─────────────────────────────────────────────┴───────────────────────────────────┘" << endl;

    // 클리닝 및 커서 고정
    SetColor(15);
    cout << "                                                                                                    " << endl;
    cout << "                                                                                                    " << endl;
    COORD coord = { 0, 11 };
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
    int choice;
    char hc;

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

    // 스탯 최종 계산
    data.hp = data.vit;
    data.maxHp = data.vit;
    data.atkDmg = data.str * 0.25f;
    data.atkSpd = data.dex / 10.0f;

    AddLog(data, "Welcome, " + data.name + ". Your journey begins.");
    LoadingEffect(data, "Generating Character Data");
}

bool StartBattle(GameData& data) {
    data.currentMonster.name = "Elite Goblin";
    data.currentMonster.maxHp = 60;
    data.currentMonster.hp = 60;
    data.currentMonster.active = true;

    AddLog(data, "A " + data.currentMonster.name + " appeared!");
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
                data.hp -= 20;
                AddLog(data, "Goblin counter-attacks! You lost 20 HP.");
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
    for (int i = 0; i < 2; i++) {
        int r = rand() % 3;
        string item = (r == 0) ? "Gold" : (r == 1) ? "Potion" : "Old Sword";
        AddLog(data, "Found: [" + item + "]");
        RenderScene(data);
        Sleep(500);
    }
    cout << " Press any key to continue...";
    system("pause > nul");
}

// --- [ 포인터 개념 확인 함수 ] ---
// 
// 1. 포인터의 기본: 주소, 참조, 역참조 확인
void practiceBasicPointer() {
    cout << "=== 1. Basic Pointer Practice ===" << endl;
    int gold = 500;
    int* ptr = &gold; // gold의 주소를 ptr에 저장

    cout << "1. 변수 gold의 값: " << gold << endl;
    cout << "2. 변수 gold의 주소 (&gold): " << &gold << endl;
    cout << "3. 포인터 ptr이 들고 있는 값 (주소): " << ptr << endl;
    cout << "4. 포인터로 접근한 값 (*ptr): " << *ptr << endl;

    *ptr = 1000; // 역참조를 통해 원본 값 변경
    cout << "5. 역참조로 수정한 후 gold의 값: " << gold << endl << endl;
}

// 2. 포인터 변수 자체의 크기 (자료형과 무관함)
void practicePointerSize() {
    cout << "=== 2. Pointer Size Practice ===" << endl;
    char* cPtr;
    int* iPtr;
    double* dPtr;
    long long* lPtr;

    // 가리키는 대상의 크기 vs 주소값 자체의 크기
    cout << "char* 크기: " << sizeof(cPtr) << " bytes" << endl;
    cout << "int* 크기: " << sizeof(iPtr) << " bytes" << endl;
    cout << "double* 크기: " << sizeof(dPtr) << " bytes" << endl;
    cout << "long long* 크기: " << sizeof(lPtr) << " bytes" << endl;
    cout << "=> 어떤 타입이든 '주소'의 크기는 시스템(64/32bit)에 따라 동일함!" << endl << endl;
}

// 3. 포인터 연산: 주소값이 점프하는 규칙
void practicePointerArithmetic() {
    cout << "=== 3. Pointer Arithmetic Practice ===" << endl;
    int arr[3] = { 10, 20, 30 };
    int* p = arr; // 배열 이름은 첫 번째 요소의 주소

    cout << "현재 주소 (p): " << p << " | 값: " << *p << endl;
    cout << "다음 주소 (p+1): " << (p + 1) << " | 값: " << *(p + 1) << endl;

    // 주소값의 차이를 계산 (16진수 계산 확인용)
    uintptr_t addr1 = (uintptr_t)p;
    uintptr_t addr2 = (uintptr_t)(p + 1);
    cout << "주소값 차이: " << addr2 - addr1 << " bytes (sizeof(int)만큼 차이남)" << endl << endl;
}

// 실습하고 싶은 함수의 주석을 해제하세요.
//practiceBasicPointer();
//practicePointerSize();
//practicePointerArithmetic();


int main() {
/*    HideCursor();
    srand((unsigned int)time(NULL));

    GameData player;
    // 초기 기본 스탯
    player.str = 50; player.dex = 50; player.vit = 100; player.eng = 50;
    player.currentMonster.active = false;

    // 1. 캐릭터 생성 (여기서 이름 설정!)
    CreateCharacter(player);

    // 2. 전투 시작
    if (StartBattle(player)) {
        // 3. 전리품 획득
        Looting(player);
    }
    else {
        SetColor(12);
        AddLog(player, "You died...");
        RenderScene(player);
        cout << " --- GAME OVER ---" << endl;
    }

    SetColor(15);*/
    practiceBasicPointer();
    practicePointerSize();
    practicePointerArithmetic();
    return 0;
}