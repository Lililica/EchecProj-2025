#include "app.hpp"

void App::setup_app()
{
    this->m_state = screenState::Accueil;
}

void App::calcul_content()
{
}

void App::draw_content() const
{
    for (int x{0}; x < this->tailleGrid; x++)
    {
        for (int y{0}; y < this->tailleGrid; y++)
        {
            if (y != 0)
                ImGui::SameLine();
            ImGui::PushID((x * this->tailleGrid) + y);
            if (ImGui::Button(std::to_string((x * this->tailleGrid) + y).c_str(), ImVec2{50.f, 50.f}))
            {
                std::cout << std::to_string((x * this->tailleGrid) + y) << "\n";
            }
            ImGui::PopID();
        }
    }
}
