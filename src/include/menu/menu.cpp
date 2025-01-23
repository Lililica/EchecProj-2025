#include "menu.hpp"
#include <imgui.h>
#include "include/utils/bouton.hpp"

void Menu::setup_menu()
{
    Button play;
    play.m_name    = "Play";
    play.m_message = "Play";
    m_buttons.push_back(play);
    Button quit;
    quit.m_name    = "Quit";
    quit.m_message = "Quit";
    m_buttons.push_back(quit);
}

void Menu::update_menu(screenState& state)
{
    if (m_update.update)
    {
        if (m_update.message == "Play")
        {
            state = screenState::Game;
        }
        m_update.update = false;
    }
}

void Menu::draw_menu()
{
    ImVec2 screenSize = ImGui::GetWindowSize();
    ImVec2 buttonSize = ImVec2{200, 100};
    int    compteur   = 0;

    for (Button& b : m_buttons)
    {
        ImVec2 buttonPos = ImVec2((screenSize.x - buttonSize.x) / 2, ((screenSize.y - buttonSize.y) / 2) - 100 + static_cast<float>(compteur) * 110);
        ImGui::SetCursorPos(buttonPos);
        if (ImGui::Button(b.m_name.c_str(), buttonSize))
        {
            m_state          = screenState::Game;
            m_update.update  = true;
            m_update.message = b.m_message;
        }
        compteur++;
    }
}