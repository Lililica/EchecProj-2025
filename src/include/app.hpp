#pragma once
#include <imgui.h>
#include <cstdint>
#include "./include/board/board.hpp"
#include "./include/render/render.hpp"
#include "include/menu/menu.hpp"

class App {
private:
    screenState m_state = screenState::Accueil;

    Board  m_board;
    Render m_render;
    Menu   m_menu;

public:
    void setTailleGrid(int tailleGrid) { m_board.parameter.tailleGrid = tailleGrid; }
    void setFont(ImFont* font) { m_board.parameter.fontChess = font; }

    void setup_app();
    void update_app();
};