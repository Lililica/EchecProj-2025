#pragma once

#include <imgui.h>
#include <cstdint>
#include "Game/game.hpp"
#include "Game/gameChaos.hpp"
#include "Game/gameClassic.hpp"
#include "Menu/menu.hpp"
#include "Render/renderIMGUI.hpp"

enum class GameMode : std::uint8_t { CLASSIC,
                                     CHAOS };

struct GameDef {
    GameClassic classic;
    GameChaos   chaos;
};

struct MenuDef {
};

class App {
private:
    // Game
    Game*   _currentGame = nullptr;
    GameDef _myGames;

    // Menu
    Menu*   _currentMenu;
    MenuDef _myMenus;

    // Render
    RenderImGui _render2D;

public:
    // App Utils
    void setup_app();
    void update_app();

    // Game
    void select_game(GameMode mode);
    void set_chess_font(ImFont* font);

    // Menu
};