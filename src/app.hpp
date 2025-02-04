#pragma once

#include "Game/game.hpp"
#include "Game/gameChaos.hpp"
#include "Game/gameClassic.hpp"
#include "Render/renderIMGUI.hpp"

struct GameDef {
    GameClassic classic;
    GameChaos   chaos;
};

class App {
private:
    Game*   _currentGame = nullptr;
    GameDef _myGames;

    RenderImGui _render2D;

public:
    void setup_app();
    void update_app();
};