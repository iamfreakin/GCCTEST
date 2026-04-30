#include "ItemData.h"

// 아이템 추가시 이 파일만 수정하면 됨

unordered_map<int, ItemData> createItemDB()
{
    // 100번대 Consumable / 200번대 Weapon / 300번대 Armor / 400번대 ETC 
    unordered_map<int, ItemData> db;
    db[101] = {"Healing Potion", ItemType::Consumable};
    db[102] = {"Mana Potion", ItemType::Consumable};
    db[103] = {"Rejuvenation Potion", ItemType::Consumable};
    db[201] = {"Broad Sword", ItemType::Weapon};
    db[202] = {"Short Sword", ItemType::Weapon};
    db[203] = {"Fire Staff", ItemType::Weapon};
    db[204] = {"War Staff", ItemType::Weapon};
    db[301] = {"Leather Armor", ItemType::Armor};
    db[302] = {"Full Plate Armor", ItemType::Armor};
    db[303] = {"Robe", ItemType::Armor};
    db[304] = {"Shield", ItemType::Armor};
    db[401] = {"Gold coin", ItemType::ETC};
    db[402] = {"Statue", ItemType::ETC};
    db[403] = {"Gem", ItemType::ETC};
    db[404] = {"Crystal", ItemType::ETC};
    return db;
}
