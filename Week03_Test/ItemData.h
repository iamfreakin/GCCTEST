#pragma once
#include <unordered_map>

#include "Item.h"

// Item클래스는 추후 상속/기능 등이 추가 될 수 있기 때문에
// ItemData 구조체로 데이터를 분리
struct ItemData
{
    string name;
    ItemType type;
};

unordered_map<int, ItemData> createItemDB(); // 아이템 DB 생성 함수
