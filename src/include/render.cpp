#include "render.hpp"
#include <imgui.h>
#include <iostream>
// #include "quick_imgui/quick_imgui.hpp"

void Render::draw_content(Board& board)
{
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(parameter.itemSpacing, parameter.itemSpacing));
    for (int x{0}; x < board.tailleGrid; x++)
    {
        for (int y{0}; y < board.tailleGrid; y++)
        {
            if (y != 0)
                ImGui::SameLine();
            parameter.foundIt = false;

            check_pion(board, x, y);
            check_tour(board, x, y);
            check_cavalier(board, x, y);
            check_fou(board, x, y);
            check_dame(board, x, y);
            check_roi(board, x, y);

            if (!parameter.foundIt)
            {
                ImGui::PushID((x * board.tailleGrid) + y);
                if (ImGui::Button(std::to_string((x * board.tailleGrid) + y).c_str(), ImVec2{50.f, 50.f}))
                {
                    std::cout << std::to_string((x * board.tailleGrid) + y) << "\n";
                }
                ImGui::PopID();
            }
        }
    }
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
