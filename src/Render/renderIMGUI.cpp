#include "renderIMGUI.hpp"
#include <imgui.h>
#include "Game/game.hpp"

void RenderImGui::draw_content(Game& currentGame)
{
    for (int x{0}; x < currentGame.getGridSize(); ++x)
    {
        for (int y{0}; y < currentGame.getGridSize(); ++y)
        {
            if (y == 0)
                ImGui::SameLine();

            ImGui::PushID(x * currentGame.getGridSize() + y);

            if (ImGui::Button("A", ImVec2{10., 10.}))
            {
                // Do something
            }

            ImGui::PopID();
        }
    }
}
