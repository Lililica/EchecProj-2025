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

void App::loop_imgui()
{
    // Init ImGui for a new frame
    imgui_pre_render();

    // Manage game selection and menu state
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

    // Render ImGui
    imgui_render();
}

void App::loop_opengl()
{
    this->_render3D.getManager()->update_window_size();

    glClearColor(1.f, 0.5f, 0.5f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // if (this->_currentMenu->get_state() == MenuState::IN_GAME)
    // {
    this->_render3D.draw_content(this->_currentGame);
    // }
}