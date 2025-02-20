#include "Menu/menu.hpp"
#include <imgui.h>
#include <iostream>

void Menu::change_menu(MenuState state)
{
}

void Menu::draw_me()
{
    for (const auto& button : this->_buttonList)
    {
        if (ImGui::Button(button.name.c_str(), ImVec2{button.taille.first, button.taille.second}))
        {
            set_state(button.action());
        }
    }
}