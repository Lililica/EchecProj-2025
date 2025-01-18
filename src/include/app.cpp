#include "app.hpp"
// #include "include/utils.hpp"

void App::setup_app()
{
    this->m_state = screenState::Accueil;
    this->m_board.setup_board();
    this->m_menu.setup_menu();
}

void App::update_app()
{
    if (this->m_state == screenState::Accueil)
    {
        if (this->m_menu.m_update.update)
            this->m_menu.update_menu(this->m_state);
        this->m_menu.draw_menu();
    }
    if (this->m_state == screenState::Game)
    {
        this->m_board.calcul_content_game();
        this->m_render.draw_content_game(this->m_board);
    }
}
