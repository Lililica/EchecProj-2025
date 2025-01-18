#include "render.hpp"
#include <imgui.h>
#include "../board/case.hpp"
// #include "quick_imgui/quick_imgui.hpp"

void Render::draw_content(Board& board) const
{
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(parameter.itemSpacing, parameter.itemSpacing));
    ImGui::PushFont(board.parameter.fontChess);

    for (Case& c : board.m_cases)
    {
        if (c.id % board.parameter.tailleGrid != 0)
            ImGui::SameLine();

        ImGui::PushID(c.id);

        // Change button color
        ImGui::PushStyleColor(ImGuiCol_Button, c.color);
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, c.color_hover);

        // ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.8f, 0.8f, 0.8f, 1.0f));
        // ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.2f, 0.2f, 0.2f, 1.0f));

        if (ImGui::Button(c.pieceName.c_str(), ImVec2{c.size, c.size}))
        {
            board.parameter.update.callAnUpdate = c.id;

            // if (board.parameter.currentSelectionPiece == -1 && c.isOccuped)
            // {
            //     board.parameter.currentSelectionPiece = c.id;
            //     c.isSelected                          = true;
            //     c.action(board.parameter.callAnUpdate, board.parameter.updateList);
            // }
            // else if (std::find(board.parameter.updateList.begin(), board.parameter.updateList.end(), c.id) != board.parameter.updateList.end())
            // {
            //     board.m_cases[board.parameter.currentSelectionPiece].isSelected = false;
            //     board.parameter.currentSelectionPiece                           = -1;
            //     c.action(board.parameter.callAnUpdate, board.parameter.updateList);
            // }
        }

        ImGui::PopStyleColor(2);

        ImGui::PopID();
    }
    ImGui::PopFont();
    // check_pion(temp, x, y);
    // check_tour(temp, x, y);
    // check_cavalier(temp, x, y);
    // check_fou(temp, x, y);
    // check_dame(temp, x, y);
    // check_roi(temp, x, y);
    ImGui::PopStyleVar();
}
