#include "GameData.h"

void GameData::AddLog(const string& message) {
    logs.push_back(message);
    if (logs.size() > 8) logs.pop_front();
}