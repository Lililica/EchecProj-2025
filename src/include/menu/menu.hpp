#pragma once
#include <string>
#include <vector>
#include "include/utils/bouton.hpp"

enum class screenState : std::uint8_t { Accueil,
                                        Game,
                                        Loading };

struct MenuUpdate {
    bool        update = false;
    std::string message;
};

struct Menu {
    screenState         m_state = screenState::Accueil;
    std::vector<Button> m_buttons;
    MenuUpdate          m_update;

    void setup_menu();
    void update_menu(screenState& state);
    void draw_menu();
};
