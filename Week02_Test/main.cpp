#include <iostream>

using namespace std;

int main()
{
    char userName[50];
    char charactorClass[50];
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
    cout << "Input your Class : ";
    cin >> charactorClass;

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

    // 3. sizeof 연산자를 이용한 메모리 크기 확인
    cout << "[Memory Check] int type size: " << sizeof(hp) << " bytes\n";
    cout << "[Memory Check] bool type size: " << sizeof(isHardcore) << " bytes\n";

    cout << "Fire Resist : " << fireResist << '\n';
	cout << "Lightning Resist : " << lightningResist << '\n';
	cout << "Cold Resist : " << coldResist << '\n';
	cout << "Poison Resist : " << poisonResist << '\n';

    return 0;
}