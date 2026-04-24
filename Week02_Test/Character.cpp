#include "Character.h"

Character::Character(std::string n, int str, int dex, int vit, int eng, int lv = 1)
: name(n), strength(str), dexterity(dex), vitality(vit), energy(eng), level(lv),
  mp(0), maxMp(0), movingSpeed(1.0), fireResist(0), coldResist(0), 
  lightningResist(0), poisonResist(0) {
    // HP와 공격력 등은 자식 클래스의 Initialize에서 세부 계산 예정
}