#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <iomanip>
#include <deque> // 로그 목록 관리를 위해 추가 

using namespace std;

struct GameData {
    string name;
    string job;
    int level = 1;
    int hp, mp;
    float atkSpd, atkDmg;
    int str, dex, vit, eng;
    bool hardcore;
    deque<string> logs; // 여러 줄의 로그를 담는 저장소 
};

// 로그를 추가하고 최대 줄 수를 유지하는 함수
void AddLog(GameData& data, string message) {
    data.logs.push_back(message); // 새 로그를 맨 뒤에 추가 
    if (data.logs.size() > 6) {    // 최대 6줄까지만 유지 (상태창 높이에 맞춤)
        data.logs.pop_front();    // 가장 오래된 로그 삭제 
    }
}

// 1. 전체 화면 렌더링 함수 (멀티라인 지원)
void RenderScene(const GameData& data) {
    system("cls");

    cout << "====================================================================================================" << endl;
    cout << " [ GAME PROGRESS LOG ]                                      | [ CHARACTER STATUS ]" << endl;
    cout << "====================================================================================================" << endl;

    // 우측 상태창 항목을 배열로 미리 준비
    string status[6];
    status[0] = "  NAME : " + data.name;
    status[1] = "  CLASS: " + data.job + " (Lv." + to_string(data.level) + ")";
    status[2] = "  HP   : " + to_string(data.hp) + " / MP: " + to_string(data.mp);
    status[3] = "  ATK  : " + to_string((int)data.atkDmg) + " / SPD: " + to_string(data.atkSpd).substr(0, 3);
    status[4] = "  STATS: STR:" + to_string(data.str) + " DEX:" + to_string(data.dex) + " VIT:" + to_string(data.vit);
    status[5] = "  MODE : " + string(data.hardcore ? "HARDCORE" : "STANDARD");

    // 좌측 로그와 우측 상태창을 한 줄씩 짝지어 출력
    for (int i = 0; i < 6; i++) {
        string displayLog = (i < data.logs.size()) ? " > " + data.logs[i] : "";
        cout << left << setw(60) << displayLog << "| " << status[i] << endl;
    }

    cout << "====================================================================================================" << endl;
}

// 2. 캐릭터 생성 함수
void CreateCharacter(GameData& data) {
    int classChoice;
    char hardcoreChoice;

    cout << " [ Character Creation ] " << endl;
    cout << " Input your name : "; cin >> data.name;
    cout << "\n (1) Warrior  (2) Rogue  (3) Sorcerer\n Input class number : "; cin >> classChoice;

    switch (classChoice) {
    case 1: data.job = "Warrior"; break;
    case 2: data.job = "Rogue"; break;
    case 3: data.job = "Sorcerer"; break;
    default: data.job = "Unknown"; break;
    }

    cout << " Enable Hardcore Mode? (1) Yes / (0) No : "; cin >> hardcoreChoice;
    data.hardcore = (hardcoreChoice == '1');

    AddLog(data, "Welcome, " + data.name + ". Your journey begins now.");
}

// 3. 전투 시스템 함수 (멀티라인 로그 활용)
bool StartBattle(GameData& data) {
    int goblinHp = 30;
    int action;
    AddLog(data, "A Goblin appeared from the shadows!");

    while (goblinHp > 0 && data.hp > 0) {
        RenderScene(data);

        cout << "\n [Action] 1.Attack  : ";
        cin >> action;

        if (action == 1) {
            goblinHp -= (int)data.atkDmg;
            AddLog(data, "You dealt " + to_string((int)data.atkDmg) + " damage to Goblin.");

                if (goblinHp > 0) {
                    data.hp -= 30;
                    AddLog(data, "Goblin counter-attacks! You lost 30 HP.");
                }
        }
        else {
            AddLog(data, "Invalid action! You stumbled.");
        }
    }
    return data.hp > 0;
}

// 4. 전리품 획득 함수
void Looting(GameData& data) {
    srand((unsigned int)time(NULL));
    AddLog(data, "Searching the Goblin's remains...");

    for (int i = 1; i <= 2; i++) { // 너무 많으면 로그가 밀리므로 2개만
        int roll = rand() % 4;
        string item = (roll == 0) ? "Gold" : (roll == 1) ? "Potion" : (roll == 2) ? "Weapon" : "Armor";
        AddLog(data, "Found item: [" + item + "]");
    }

    RenderScene(data);
    cout << "\n Press any key to continue...";
    system("pause > nul");
}

int main() {
    GameData player;
    player.str = 50; player.dex = 50; player.vit = 50; player.eng = 50;
    player.hp = player.vit * 2;
    player.mp = (int)(player.eng * 1.5);
    player.atkDmg = player.str * 0.2f;
    player.atkSpd = player.dex / 10.0f;

    CreateCharacter(player);

    if (StartBattle(player)) {
        AddLog(player, "Victory! You defeated the Goblin.");
        Looting(player);
    }
    else {
        AddLog(player, "You have fallen in battle...");
        RenderScene(player);
    }

    return 0;
}