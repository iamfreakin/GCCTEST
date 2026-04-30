#include "MonsterData.h"

// Monster 밸런스 조정 시, 이 파일만 수정하면 됨
unordered_map<string, MonsterData> createMonsterDB()
{
    unordered_map<string, MonsterData> db;
    
    db["Goblin"] = { 50, 0, 15,0, 50, {101, 101, 101}};
    db["FireGoblin"] = { 50 ,15 ,0 ,50, 50, {101, 102}};
    db["Skeleton"] = { 60, 0 ,0 ,50, 50, {103, 202, 101}};
    db["Wraith"] = { 50,25 ,0 ,50, 70, {301, 302}};
    db["Ghoul"] = { 70, 0 ,0 ,120, 80, {201, 102, 101}};
    db["Andariel"] = { 200, 0 ,150 ,500, 200, {101, 102}};
    
    return db;
}