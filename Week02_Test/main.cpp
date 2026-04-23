#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <iomanip>
#include <deque>
#include <windows.h>

using namespace std;

// --- [ 1. Monster 클래스 고도화 ] ---
class Monster {
private:
    string name;
    int hp;
    int maxHp;
    int attackDamage;
    bool active; // 몬스터 출현 여부

public:
    // 기본 생성자 (비활성 상태로 시작)
    Monster() : name(""), hp(0), maxHp(0), attackDamage(0), active(false) {}

    // 몬스터 생성(스폰) 함수
    void Spawn(string n, int h, int a) {
        name = n;
        hp = h;
        maxHp = h;
        attackDamage = a;
        active = true;
    }

    // Getter 함수들 (캡슐화 유지)
    string GetName() const { return name; }
    int GetHp() const { return hp; }
    int GetMaxHp() const { return maxHp; }
    int GetAtk() const { return attackDamage; }
    bool IsActive() const { return active; }
    bool IsAlive() const { return hp > 0; }

    //Setter
    void SetActive(bool val) { active = val; }

    // 데미지 처리 로직 (내부에서 처리)
    void TakeDamage(int damage) {
        hp -= damage;
        if (hp < 0) hp = 0;
    }
};

// --- [ 2. GameData 수정 ] ---
struct GameData {
    string name = "Unknown";
    string job = "None";
    int level = 1;
    int maxHp = 100;
    int hp = 100;
    int mp = 0;
    float atkSpd = 1.0f;
    float atkDmg = 10.0f;
    int str = 0, dex = 0, vit = 0, eng = 0;
    bool hardcore = false;
    int inventory[4] = { 0, 0, 0, 0 };
    deque<string> logs;

    // 기존 struct MonsterData 대신 Monster 클래스 사용
    Monster currentMonster; 
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
    SetColor(8); 
    cout << "┌──────────────────────────────┬─────────────────────────────────────────────┬───────────────────────────────────┐" << endl;
    cout << "│      [ ENEMY STATUS ]        │            [ GAME PROGRESS LOG ]            │        [ CHARACTER STATUS ]       │" << endl;
    cout << "├──────────────────────────────┼─────────────────────────────────────────────┼───────────────────────────────────┤" << endl;

    // 몬스터 객체 참조 (코드를 짧게 만들기 위함)
    const Monster& m = data.currentMonster;

    for (int i = 0; i < 7; i++) {
        SetColor(8); cout << "│";

        // 좌측 영역: Monster 클래스의 메서드 사용
        if (m.IsActive()) {
            if (i == 1) {
                SetColor(12); cout << left << setw(30) << ("  NAME : " + m.GetName());
            }
            else if (i == 2) {
                SetColor(15); cout << "  HP   : ";
                SetColor(12);
                string mBar = "[";
                int mSeg = (m.GetMaxHp() > 0) ? (m.GetHp() * 10) / m.GetMaxHp() : 0;
                for (int j = 0; j < 10; j++) mBar += (j < mSeg) ? "#" : "-";
                mBar += "] " + to_string(m.GetHp());
                cout << left << setw(21) << mBar;
            }
            else if (i == 3) {
                SetColor(12); cout << left << setw(30) << ("  ATK  : " + to_string(m.GetAtk()));
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
        string invStr = "  INV   : G:" + to_string(data.inventory[0]) + " P:" + to_string(data.inventory[1]) +
                " W:" + to_string(data.inventory[2]) + " A:" + to_string(data.inventory[3]);
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

int CriticalDamage(GameData& data) {
    return (int)(data.atkDmg * 2);
}

void LevelUp_Reference(GameData& data) {
    data.level += 1;
}

bool StartBattle(GameData& data) {
    string names[] = { "Slime", "Goblin", "Orc", "Skeleton", "Wild Wolf" };
    
    // 클래스 메서드를 통한 몬스터 생성
    data.currentMonster.Spawn(
        names[rand() % 5], 
        rand() % 41 + 30, 
        rand() % 9 + 7
    );

    AddLog(data, "A " + data.currentMonster.GetName() + " appeared!");
    
    while (data.currentMonster.IsAlive() && data.hp > 0) {
        RenderScene(data);
        int act;
        SetColor(11); cout << " [Action] 1.Attack  2.Critical : "; cin >> act;

        int d = (act == 2) ? (int)(data.atkDmg * 2) : (int)data.atkDmg;
        
        // 몬스터에게 데미지 전달 (직접 수정 X, 메서드 호출 O)
        data.currentMonster.TakeDamage(d);
        AddLog(data, "You hit " + data.currentMonster.GetName() + "! (-" + to_string(d) + ")");
        
        if (data.currentMonster.IsAlive()) {
            int mDmg = data.currentMonster.GetAtk();
            data.hp -= mDmg;
            AddLog(data, data.currentMonster.GetName() + " attacks! You lost " + to_string(mDmg) + " HP.");
        }
        Sleep(400);
    }

    if (data.hp > 0) {
        AddLog(data, "Victory! " + data.currentMonster.GetName() + " slain.");
        data.level++;
        data.currentMonster.SetActive(false); // 전투 종료 후 비활성화
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

int main() {
    // [1] 시스템 초기화
    HideCursor();
    srand(static_cast<unsigned int>(time(NULL)));

    // [2] 플레이어 데이터 초기 설정
    GameData player;
    player.str = 50; 
    player.dex = 50; 
    player.vit = 100; 
    player.eng = 50;
    // player.currentMonster.active = false; -> Monster 클래스 생성자에서 이미 처리됨 (삭제)

    // [3] 캐릭터 생성 단계
    CreateCharacter(player);

    // [4] 메인 게임 시나리오 진행 (전투 및 결과)
    // 기능을 변경하지 않기 위해 단판 승부 구조 유지
    bool isVictory = StartBattle(player);

    if (isVictory) {
        // 전투 승리 시 루팅 진행
        Looting(player);
    }
    else {
        // 전투 패배 시 사망 연출 및 종료 처리
        SetColor(12); // 빨간색
        AddLog(player, "You died...");
        RenderScene(player);
        
        cout << "\n" << setw(60) << " [ SYSTEM ] --- GAME OVER --- " << endl;
    }

    // [5] 시스템 종료 전 정리 (색상 복구)
    SetColor(15);
    return 0;
}

