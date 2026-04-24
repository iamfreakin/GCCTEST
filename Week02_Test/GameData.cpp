#include "GameData.h"

void GameData::AddLog(const string& message) {
    logs.push_back(message);
    if (logs.size() > 6) logs.pop_front();
}