#include "app.hpp"
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include "Game/game.hpp"
#include "Render/renderIMGUI.hpp"

void App::setup_app()
{
    this->_currentGame = &this->_myGames.classic;
    set_menu(MenuState::HOME);
    this->_myMenus.home.set_button();
    _currentGame->game_setup();
}

void App::update_app()
{
    loop_opengl();

    loop_imgui();
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
    this->_render2D.ChessFont   = font;
    this->_render2D.DefaultFont = ImGui::GetIO().Fonts->AddFontDefault();
}

void App::set_menu(MenuState state)
{
    if (state == MenuState::HOME)
        this->_currentMenu = &this->_myMenus.home;
    if (state == MenuState::IN_GAME)
        this->_currentMenu = &this->_myMenus.ingame;
    if (state == MenuState::PAUSE)
        this->_currentMenu = &this->_myMenus.pause;
}

void App::loop_imgui()
{
    ImGui_ImplGlfw_NewFrame();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();
    ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);

    ImGui::PushFont(this->_render2D.DefaultFont);
    ImGui::Begin("Echec Game");

    if (this->_currentMenu->get_state() == MenuState::HOME)
    {
        this->_currentMenu->draw_me();
    }
    if (this->_currentMenu->get_state() == MenuState::IN_GAME)
    {
        if (this->_currentGame->get_isEndGame())
        {
            this->_currentMenu->set_state(MenuState::HOME);
            this->_currentGame->game_setup();
        }
        this->_render2D.draw_content(*this->_currentGame);
    }

    ImGui::PopFont();

    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void App::loop_opengl()
{
    if (this->_currentMenu->get_state() == MenuState::IN_GAME)
    {
        this->_render3D.draw_content(this->_currentGame);
    }
}