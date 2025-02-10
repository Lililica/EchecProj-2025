#include "renderIMGUI.hpp"
#include <imgui.h>
#include "Game/Piece/piece.hpp"
#include "Game/game.hpp"

void RenderImGui::draw_content(Game& currentGame) const
{
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(parameter.spaceCase, parameter.spaceCase));
    for (int y{0}; y < currentGame.getGridSize(); ++y)
    {
        for (int x{0}; x < currentGame.getGridSize(); ++x)
        {
            Piece* piece = currentGame.get_piece(x, y);

            if (x != 0)
                ImGui::SameLine();

            int id = y * currentGame.getGridSize() + x;

            ImGui::PushID(id);
            ImGui::PushFont(this->ChessFont);

            std::string pieceName = piece ? piece->name_for_imgui() : " ";

            if (ImGui::Button(pieceName.c_str(), ImVec2{80., 80.}))
            {
                if (piece && !currentGame.is_selected_piece())
                {
                    currentGame.select_piece(piece);
                }
                else if (currentGame.is_selected_piece())
                {
                    currentGame.move_piece(x, y);
                }
            }

            ImGui::PopFont();
            ImGui::PopID();
        }
    }
    ImGui::PopStyleVar();
}
