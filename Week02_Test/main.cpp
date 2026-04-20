#include <iostream>

using namespace std;

int main()
{
    char userName[50];
    string charactorClass;
	int classChoiceInput = 0;
    char hardcoreInput;

    // // 스탯 시스템
    int strength = 50;
    int dexterity = 50;
    int vitality = 50;
    int energy = 50;

    // // 1. 다양한 자료형의 변수 선언 및 초기값 할당
    int level = 1;
    int hp = vitality * 2;
    int mp = energy * 1.5;
    float attackDamage = strength * 0.2f;
    float attackSpeed = dexterity / 10.0f;
    double movingSpeed = dexterity / 30.0;
    int fireResist = 0;
    int lightningResist = 0;
    int coldResist = 0;
    int poisonResist = 0;

    // // 하드코어 모드 여부 변수
    bool isHardcore = true;

    cout << "[ Character Creation ]\n";
    cout << "Input your name : ";
    cin >> userName;
    cout << "\nSelect your Class :\n(1) Warrior\n(2) Rogue\n(3) Sorcerer\n";
	cout << "Input class number : ";
	cin >> classChoiceInput;

    cout << "Enable Hardcore Mode? (1) Yes / (0) No : ";
    cin >> hardcoreInput;

    // // if, else if, else 조건문 사용 (참, 거짓 에 대한 분기)
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

    switch (classChoiceInput)
    {
        case 1: charactorClass = "Warrior"; break;
        case 2: charactorClass = "Rogue"; break;
        case 3: charactorClass = "Sorcerer"; break;
        default:
            charactorClass = "Unknown";
            cout << "[System] Invalid choice. Defaulting to Unknown.\n";
            break;
    }

    cout << "\n::::::::: Welcome to the Sanctuary :::::::::\n";
    cout << "User Name : [" << userName << "]\n";

    // 2. 변수에 저장된 데이터 출력
    cout << "--------------------Character Status--------------------\n";
    cout << "Class : " << charactorClass << "\n";
    cout << "Level : " << level << "\n";
    cout << "HP : " << hp << "\n";
    cout << "MP : " << mp << "\n";
    cout << "Attack Speed : " << attackSpeed << "\n";
    cout << "Strength : " << strength << "\n";
    cout << "Dexterity : " << dexterity << "\n";
    cout << "Vitality : " << vitality << "\n";
    cout << "Energy : " << energy << "\n";
    cout << "Hardcore Mode : " << isHardcore << " (1: true, 0: false)\n";
    cout << "--------------------------------------------------------\n";

    // 기본 전투 시스템 - while문 사용 (거짓일 때 까지 무한 루프)
    int goblinHp = 30; // 고블린 체력
    int action;

    cout << "\n[System] You encountered a Goblin!\n";

    // 둘 다 체력이 0보다 큰(살아있는) 동안 무한 반복
    while (goblinHp > 0 && hp > 0) {
        cout << "\n[ Goblin HP: " << goblinHp << " | My HP: " << hp << " ]\n";
        cout << "1. Attack : ";
        cin >> action;

        if (action == 1) {
            // 1. 플레이어의 공격
            goblinHp -= attackDamage;
            cout << "=> You attacked the Goblin! (-" << attackDamage << ")\n";

            // 2. 고블린의 반격
            if (goblinHp > 0) {
                hp -= 30;
                cout << "=> The Goblin attacked you! (-30)\n";
            }
        }
        else {
            cout << "=> Invalid action! You stumbled and the Goblin seized the chance!\n";
            hp -= 30;
            cout << "=> The Goblin attacked you! (-30)\n";
        }
    }

    // 전투 종료 후 결과 판정
    cout << "\n";
    if (hp <= 0) {
        cout << "[System] You died...\n";
    }
    else {
        cout << "[System] You defeated the Goblin!\n";
    }

 //   // 3. sizeof 연산자를 이용한 메모리 크기 확인
 //   cout << "[Memory Check] int type size: " << sizeof(hp) << " bytes\n";
 //   cout << "[Memory Check] bool type size: " << sizeof(isHardcore) << " bytes\n";

 //   cout << "Fire Resist : " << fireResist << '\n';
	//cout << "Lightning Resist : " << lightningResist << '\n';
	//cout << "Cold Resist : " << coldResist << '\n';
	//cout << "Poison Resist : " << poisonResist << '\n';

    return 0;
}