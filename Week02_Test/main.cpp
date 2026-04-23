#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <iomanip>
#include <deque>
#include <algorithm> // max, fill 함수 사용을 위해 추가
#include <windows.h>

using namespace std;

// --- [ 1. Monster 클래스 ] ---
class Monster {
private:
    string name;
    int hp;
    int maxHp;
    int attackDamage;
    bool active;

public:
    Monster() : name(""), hp(0), maxHp(0), attackDamage(0), active(false) {}

    void Spawn(string n, int h, int a) {
        name = n;
        hp = h;
        maxHp = h;
        attackDamage = a;
        active = true;
    }

    string GetName() const { return name; }
    int GetHp() const { return hp; }
    int GetMaxHp() const { return maxHp; }
    int GetAtk() const { return attackDamage; }
    bool IsActive() const { return active; }
    bool IsAlive() const { return hp > 0; }
    void SetActive(bool val) { active = val; }

    void TakeDamage(int damage) {
        hp = max(0, hp - damage);
    }
};

// --- [ 2. Player 클래스 ] ---
class Player {
private:
    string name, job;
    int level, hp, maxHp;
    int str, dex, vit, eng;
    float atkDmg, atkSpd;
    int inventory[4]; 

public:
    Player() : name("Unknown"), job("None"), level(1), hp(100), maxHp(100),
               str(0), dex(0), vit(0), eng(0), atkDmg(10.0f), atkSpd(1.0f) {
        fill(begin(inventory), end(inventory), 0);
    }

    void Initialize(string n, int jobChoice) {
        name = n;
        switch (jobChoice) {
            case 1: job = "Warrior";  str = 15; dex = 5;  vit = 15; break;
            case 2: job = "Rogue";    str = 8;  dex = 18; vit = 10; break;
            case 3: job = "Sorcerer"; str = 5;  dex = 10; vit = 8;  eng = 20; break;
            default: job = "Adventurer"; str = 10; dex = 10; vit = 10; break;
        }
        maxHp = vit * 10;
        hp = maxHp;
        atkDmg = (float)str * 1.5f;
        atkSpd = 1.0f + (dex * 0.05f);
    }

    void TakeDamage(int dmg) {
        hp = max(0, hp - dmg);
    }

    void LevelUp() {
        level++;
        maxHp += 20;
        hp = maxHp;
    }

    void AddItem(int type, int amount) {
        if (type >= 0 && type < 4) inventory[type] += amount;
    }

    string GetName() const { return name; }
    string GetJob() const { return job; }
    int GetLevel() const { return level; }
    int GetHp() const { return hp; }
    int GetMaxHp() const { return maxHp; }
    int GetStr() const { return str; }
    int GetDex() const { return dex; }
    int GetVit() const { return vit; }
    int GetInvItem(int idx) const { return inventory[idx]; }
    float GetAtkDmg() const { return atkDmg; }
    float GetAtkSpd() const { return atkSpd; }
    bool IsAlive() const { return hp > 0; }
};

// --- [ 3. GameData 클래스 ] ---
class GameData {
private:
    Player currentPlayer;
    Monster currentMonster;
    deque<string> logs;
    bool hardcore;
    
public:
    GameData() : hardcore(false) {}
    
    void AddLog(const string& message) {
        logs.push_back(message);
        if (logs.size() > 6) logs.pop_front();
    }

    void SetHardcore(bool val) { hardcore = val; }
    bool IsHardcore() const { return hardcore; }

    Player& GetPlayer() { return currentPlayer; }
    const Player& GetPlayer() const { return currentPlayer; }

    Monster& GetMonster() { return currentMonster; }
    const Monster& GetMonster() const { return currentMonster; }

    const deque<string>& GetLogs() const { return logs; }
};

// --- [ 4. UI 제어 유틸리티 ] ---
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
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 0 });
}

// --- [ 5. 렌더링 및 게임 로직 ] ---
void RenderScene(const GameData& data) {
    MoveCursorToTop();
    SetColor(8); 
    cout << "┌──────────────────────────────┬─────────────────────────────────────────────┬───────────────────────────────────┐" << endl;
    cout << "│      [ ENEMY STATUS ]        │            [ GAME PROGRESS LOG ]            │        [ CHARACTER STATUS ]       │" << endl;
    cout << "├──────────────────────────────┼─────────────────────────────────────────────┼───────────────────────────────────┤" << endl;

    const Monster& m = data.GetMonster();
    const Player& p = data.GetPlayer();
    const auto& logs = data.GetLogs();

    for (int i = 0; i < 7; i++) {
        SetColor(8); cout << "│";

        // 1. 좌측 (Monster)
        if (m.IsActive()) {
            if (i == 1) { SetColor(12); cout << left << setw(30) << ("  NAME : " + m.GetName()); }
            else if (i == 2) {
                SetColor(15); cout << "  HP   : ";
                SetColor(12);
                string mBar = "[";
                int mSeg = (m.GetMaxHp() > 0) ? (m.GetHp() * 10) / m.GetMaxHp() : 0;
                for (int j = 0; j < 10; j++) mBar += (j < mSeg) ? "#" : "-";
                mBar += "] " + to_string(m.GetHp());
                cout << left << setw(21) << mBar;
            }
            else if (i == 3) { SetColor(12); cout << left << setw(30) << ("  ATK  : " + to_string(m.GetAtk())); }
            else cout << setw(30) << "";
        } else cout << setw(30) << "";

        SetColor(8); cout << "│";

        // 2. 중앙 (Logs)
        string dLog = (i < logs.size()) ? " > " + logs[i] : "";
        if (dLog.find("damage") != string::npos || dLog.find("lost") != string::npos) SetColor(12);
        else if (dLog.find("Victory") != string::npos || dLog.find("Found") != string::npos) SetColor(10);
        else SetColor(15);
        cout << left << setw(45) << dLog;

        SetColor(8); cout << "│";

        // 3. 우측 (Player)
        string invStr = "  INV   : G:" + to_string(p.GetInvItem(0)) + " P:" + to_string(p.GetInvItem(1)) +
                " W:" + to_string(p.GetInvItem(2)) + " A:" + to_string(p.GetInvItem(3));
        SetColor(15);
        if (i == 0) cout << left << setw(35) << ("  NAME  : " + p.GetName());
        else if (i == 1) cout << left << setw(35) << ("  CLASS : " + p.GetJob() + " (Lv." + to_string(p.GetLevel()) + ")");
        else if (i == 2) {
            cout << "  HP    : ";
            float hpP = (float)p.GetHp() / p.GetMaxHp();
            if (hpP > 0.7) SetColor(10); else if (hpP > 0.3) SetColor(14); else SetColor(12);
            string hBar = "[";
            int hSeg = (p.GetMaxHp() > 0) ? (p.GetHp() * 10) / p.GetMaxHp() : 0;
            for (int j = 0; j < 10; j++) hBar += (j < hSeg) ? "#" : "-";
            hBar += "] " + to_string(p.GetHp());
            cout << left << setw(25) << hBar;
        }
        else if (i == 3) { SetColor(15); cout << left << setw(35) << ("  ATK   : " + to_string((int)p.GetAtkDmg()) + " / SPD: " + to_string(p.GetAtkSpd()).substr(0, 3)); }
        else if (i == 4) { SetColor(15); cout << left << setw(35) << ("  STATS : S:" + to_string(p.GetStr()) + " D:" + to_string(p.GetDex()) + " V:" + to_string(p.GetVit())); }
        else if (i == 5) { SetColor(14); cout << left << setw(35) << invStr; }
        else { SetColor(15); cout << left << setw(35) << ("  MODE  : " + string(data.IsHardcore() ? "HARDCORE" : "STANDARD")); }

        SetColor(8); cout << "│" << endl;
    }
    cout << "└──────────────────────────────┴─────────────────────────────────────────────┴───────────────────────────────────┘" << endl;
}

void LoadingEffect(GameData& data, string message) {
    for (int i = 0; i < 3; i++) {
        RenderScene(data);
        SetColor(14);
        cout << " [System] " << message;
        for (int j = 0; j <= i; j++) cout << ".";
        Sleep(300);
    }
}

void CreateCharacter(GameData& data) {
    string n; int c; char hc;
    system("cls");
    SetColor(11);
    cout << "┌────────────────────────────────────────────────────────────┐" << endl;
    cout << "│                [ CHARACTER CREATION ]                      │" << endl;
    cout << "└────────────────────────────────────────────────────────────┘" << endl;
    SetColor(15);
    cout << " > Input your name : "; cin >> n;
    cout << "\n > (1)Warrior (2)Rogue (3)Sorcerer / Choice: "; cin >> c;
    cout << " > Enable Hardcore Mode? (1)Yes (0)No : "; cin >> hc;
    
    data.SetHardcore(hc == '1');
    data.GetPlayer().Initialize(n, c);
    data.AddLog("Welcome, " + data.GetPlayer().GetName() + ". Your journey begins.");
    LoadingEffect(data, "Generating Character Data");
}

bool StartBattle(GameData& data) {
    string names[] = { "Slime", "Goblin", "Orc", "Skeleton", "Wild Wolf" };
    data.GetMonster().Spawn(names[rand() % 5], rand() % 41 + 30, rand() % 9 + 7);

    data.AddLog("A " + data.GetMonster().GetName() + " appeared!");
    
    while (data.GetMonster().IsAlive() && data.GetPlayer().IsAlive()) {
        RenderScene(data);
        int act;
        SetColor(11); cout << " [Action] 1.Attack  2.Critical : "; cin >> act;

        int d = (act == 2) ? (int)(data.GetPlayer().GetAtkDmg() * 2) : (int)data.GetPlayer().GetAtkDmg();
        data.GetMonster().TakeDamage(d);
        data.AddLog("You hit " + data.GetMonster().GetName() + "! (-" + to_string(d) + ")");
        
        if (data.GetMonster().IsAlive()) {
            int mDmg = data.GetMonster().GetAtk();
            data.GetPlayer().TakeDamage(mDmg);
            data.AddLog(data.GetMonster().GetName() + " attacks! You lost " + to_string(mDmg) + " HP.");
        }
        Sleep(400);
    }

    if (data.GetPlayer().IsAlive()) {
        data.AddLog("Victory! " + data.GetMonster().GetName() + " slain.");
        data.GetPlayer().LevelUp();
        data.GetMonster().SetActive(false);
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
            case 0: itemName = "Gold"; data.GetPlayer().AddItem(0, (rand() % 50 + 10)); break;
            case 1: itemName = "Potion"; data.GetPlayer().AddItem(1, 1); break;
            case 2: itemName = "Old Sword"; data.GetPlayer().AddItem(2, 1); break;
            case 3: itemName = "Armor Plate"; data.GetPlayer().AddItem(3, 1); break;
        }
        data.AddLog("Found: [" + itemName + "]");
        RenderScene(data);
        Sleep(500);
    }
    cout << " Inventory updated! Press any key to continue... ";
    system("pause > nul");
}

int main() {
    HideCursor();
    srand(static_cast<unsigned int>(time(NULL)));

    GameData game;

    CreateCharacter(game);

    if (StartBattle(game)) {
        Looting(game);
    }
    else {
        SetColor(12);
        game.AddLog("You died...");
        RenderScene(game);
        cout << "\n" << setw(60) << " [ SYSTEM ] --- GAME OVER --- " << endl;
    }

    SetColor(15);
    return 0;
}