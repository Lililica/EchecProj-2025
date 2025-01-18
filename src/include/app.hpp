#pragma once
#include <imgui.h>
#include <cstdint>
#include "./include/board/board.hpp"
#include "./include/render/render.hpp"

enum class screenState : std::uint8_t { Accueil,
                                        Game,
                                        Loading };

class App {
private:
    screenState m_state = screenState::Accueil;

    Board  m_board;
    Render m_render;

public:
    void setTailleGrid(int tailleGrid) { m_board.parameter.tailleGrid = tailleGrid; }
    void setFont(ImFont* font) { m_board.parameter.fontChess = font; }

    void setup_app();
    void update_app();
};