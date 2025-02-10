#include "app.hpp"
#include "Game/board.hpp"
#include "Game/game.hpp"
#include "Render/renderIMGUI.hpp"

void App::setup_app()
{
    this->_currentMenu->change_menu(MenuState::HOME);
    this->_currentGame = &this->_myGames.classic;
    _currentGame->game_setup();
}

void App::update_app()
{
    _render2D.draw_content(*_currentGame);
}

void App::select_game(GameMode mode)
{
    if (mode == GameMode::CLASSIC)
        this->_currentGame = &this->_myGames.classic;
    if (mode == GameMode::CHAOS)
        this->_currentGame = &this->_myGames.chaos;
}

void App::set_chess_font(ImFont* font)
{
    this->_render2D.ChessFont = font;
}
