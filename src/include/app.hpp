#pragma once
#include <cstdint>
#include "./include/board/board.hpp"
#include "./include/render/render.hpp"

enum class screenState : std::uint8_t { Accueil,
                                        Game,
                                        Loading };

class App {
private:
    screenState m_state = screenState::Accueil;
    Board       m_board;
    Render      m_render;

public:
    void setTailleGrid(int tailleGrid) { m_board.tailleGrid = tailleGrid; }

    void setup_app();
    void update_app();
};