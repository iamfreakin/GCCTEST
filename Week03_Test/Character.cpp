#include "Character.h"

Character::Character(int str, int dex, int vit, int en, int lv)  // 단순 값 세팅 초기화
// 외부입력 값 세팅 초기화 (: 이후쓴다)
    : strength(str), dexterity(dex), vitality(vit), energy(en), level(lv),
    fireResist(0), coldResist(0), lightningResist(0), poisonResist(0)
{
    // 계산이 필요한 값 세팅 초기화 ({} 안에쓴다)
    maxHp = vitality * 2; 
    hp = maxHp;
    maxMp = (int)energy * 1.5f;
    mp = maxMp;
    attackDamage = strength * 0.2f;
    attackSpeed = dexterity / 10.0f;
    movingSpeed = dexterity / 30.0f;
}

void Character::TakeDamage(int damage)
{
    hp -= damage;
    if (hp <= 0) hp = 0;
}

int Character::Attack() const
{
    return (int)attackDamage; 
}

void Character::Heal(int amount) { hp = std::min(hp + amount, maxHp); }