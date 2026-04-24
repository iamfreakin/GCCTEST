#include "GameplayManager.h"

int main() {
    ConsoleSystem::HideCursor();
    srand(static_cast<unsigned int>(time(NULL)));

    GameData game;
    
    GameplayManager::CreateCharacter(game);

    if (GameplayManager::StartBattle(game)) {
        GameplayManager::Looting(game);
    }
    else {
        ConsoleSystem::SetColor(12);
        game.AddLog("You died...");
        GameRenderer::RenderScene(game);
        cout << "\n" << setw(60) << " [ SYSTEM ] --- GAME OVER --- " << endl;
    }

    ConsoleSystem::SetColor(15);
    return 0;
}