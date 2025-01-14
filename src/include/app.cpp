#include "app.hpp"
// #include "include/utils.hpp"

void App::setup_app()
{
    this->m_board.setup_board();
}

void App::update_app()
{
    this->m_board.calcul_content();
    this->m_render.draw_content(this->m_board);
}
