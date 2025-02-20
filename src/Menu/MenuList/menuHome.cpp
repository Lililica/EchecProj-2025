#include "menuHome.hpp"
#include <functional> // Add this include for std::function
#include <iostream>
#include <utility>
#include "Menu/menu.hpp"

void MenuHome::set_button()
{
    Button PlayButton;
    PlayButton.name   = "Play";
    PlayButton.pos    = std::make_pair(100, 100);
    PlayButton.taille = std::make_pair(200, 150);
    PlayButton.action = []() {
        return MenuState::IN_GAME;
    };
    push_button(PlayButton);
    // push_button("Play", std::make_pair(100, 100), std::make_pair(200, 150));
    // push_button("Parameter", std::make_pair(100, 300), std::make_pair(200, 150));
    // push_button("Quit", std::make_pair(100, 500), std::make_pair(200, 150));
}