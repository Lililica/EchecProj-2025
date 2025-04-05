#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include "Render/renderIMGUI.hpp"
#include "app.hpp"

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

void App::imgui_pre_render()
{
    ImGui_ImplGlfw_NewFrame();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();
    ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);

    ImGui::PushFont(this->_render2D.DefaultFont);
    ImGui::Begin("Echec Game");
}

void App::imgui_render()
{
    ImGui::PopFont();

    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
