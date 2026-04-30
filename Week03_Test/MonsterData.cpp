#include "MonsterData.h"

// Monster 밸런스 조정 시, 이 파일만 수정하면 됨
unordered_map<string, MonsterData> createMonsterDB()
{
    unordered_map<string, MonsterData> db;
    
    db["Goblin"] =       { 50, 0, 10,0, 50, {101, 201, 402}};
    db["FireGoblin"] =   { 60, 5, 15,0, 50, {101, 401, 402}};
    db["Skeleton"] =     { 60, 20, 20,0, 50, {101, 301, 402}};
    db["Wraith"] =      { 50, 10, 30,0, 50, {101, 201, 402}};
    db["Ghoul"] =       { 70, 10, 120,0, 50, {101, 301, 302}};
    db["Andariel"] =    { 200, 10, 500,0, 50, {101, 301, 102}};
    
    return db;
}