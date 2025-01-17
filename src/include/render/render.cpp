#include "render.hpp"
#include <imgui.h>
#include <iostream>
#include "../board/case.hpp"
// #include "quick_imgui/quick_imgui.hpp"

void Render::draw_content(Board& board)
{
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(parameter.itemSpacing, parameter.itemSpacing));
    ImGui::PushFont(board.parameter.fontChess);

    for (Case& c : board.m_cases)
    {
        if (c.id % board.tailleGrid != 0)
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

void Render::check_pion(Board& board, int x, int y)
{
    for (pion& piece : board.m_pions.m_piecesListe)
    {
        if (piece.getPos() == Vec2<int>(x, y))
        {
            ImGui::PushID((x * board.tailleGrid) + y);
            if (ImGui::Button(piece.getName().c_str(), ImVec2{50.f, 50.f}))
            {
                std::cout << std::to_string((x * board.tailleGrid) + y) << "\n";
            }

            ImGui::PopID();
            parameter.foundIt = true;
        }
    }
}

void Render::check_tour(Board& board, int x, int y)
{
    for (tour& piece : board.m_tours.m_piecesListe)
    {
        if (piece.getPos() == Vec2<int>(x, y))
        {
            ImGui::PushID((x * board.tailleGrid) + y);
            if (ImGui::Button(piece.getName().c_str(), ImVec2{50.f, 50.f}))
            {
                std::cout << std::to_string((x * board.tailleGrid) + y) << "\n";
            }
            ImGui::PopID();
            parameter.foundIt = true;
            break;
        }
    }
}

void Render::check_cavalier(Board& board, int x, int y)
{
    for (cavalier& piece : board.m_cavaliers.m_piecesListe)
    {
        if (piece.getPos() == Vec2<int>(x, y))
        {
            ImGui::PushID((x * board.tailleGrid) + y);
            if (ImGui::Button(piece.getName().c_str(), ImVec2{50.f, 50.f}))
            {
                std::cout << std::to_string((x * board.tailleGrid) + y) << "\n";
            }
            ImGui::PopID();
            parameter.foundIt = true;
            break;
        }
    }
}

void Render::check_fou(Board& board, int x, int y)
{
    for (fou& piece : board.m_fous.m_piecesListe)
    {
        if (piece.getPos() == Vec2<int>(x, y))
        {
            ImGui::PushID((x * board.tailleGrid) + y);
            if (ImGui::Button(piece.getName().c_str(), ImVec2{50.f, 50.f}))
            {
                std::cout << std::to_string((x * board.tailleGrid) + y) << "\n";
            }
            ImGui::PopID();
            parameter.foundIt = true;
            break;
        }
    }
}

void Render::check_dame(Board& board, int x, int y)
{
    for (dame& piece : board.m_dames.m_piecesListe)
    {
        if (piece.getPos() == Vec2<int>(x, y))
        {
            ImGui::PushID((x * board.tailleGrid) + y);
            if (ImGui::Button(piece.getName().c_str(), ImVec2{50.f, 50.f}))
            {
                std::cout << std::to_string((x * board.tailleGrid) + y) << "\n";
            }
            ImGui::PopID();
            parameter.foundIt = true;
            break;
        }
    }
}

void Render::check_roi(Board& board, int x, int y)
{
    for (roi& piece : board.m_rois.m_piecesListe)
    {
        if (piece.getPos() == Vec2<int>(x, y))
        {
            ImGui::PushID((x * board.tailleGrid) + y);
            if (ImGui::Button(piece.getName().c_str(), ImVec2{50.f, 50.f}))
            {
                std::cout << std::to_string((x * board.tailleGrid) + y) << "\n";
            }
            ImGui::PopID();
            parameter.foundIt = true;
            break;
        }
    }
}
