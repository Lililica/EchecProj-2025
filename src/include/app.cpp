#include "app.hpp"
#include "include/utils.hpp"

void App::setup_app()
{
    this->m_state = screenState::Loading;
    this->push_piece();
    this->m_state = screenState::Accueil;
}

void App::calcul_content()
{
    this->m_state = screenState::Loading;
    this->m_state = screenState::Game;
}

void App::draw_content()
{
    for (int x{0}; x < this->tailleGrid; x++)
    {
        for (int y{0}; y < this->tailleGrid; y++)
        {
            if (y != 0)
                ImGui::SameLine();
            bool foundIt = false;
            for (pion piece : this->m_pions.m_piecesListe)
            {
                if (piece.getPos() == Vec2<int>(x, y))
                {
                    ImGui::PushID((x * this->tailleGrid) + y);
                    if (ImGui::Button(piece.getName().c_str(), ImVec2{50.f, 50.f}))
                    {
                        std::cout << std::to_string((x * this->tailleGrid) + y) << "\n";
                    }
                    ImGui::PopID();
                    foundIt = true;
                }
            }
            for (tour piece : this->m_tours.m_piecesListe)
            {
                if (piece.getPos() == Vec2<int>(x, y))
                {
                    ImGui::PushID((x * this->tailleGrid) + y);
                    if (ImGui::Button(piece.getName().c_str(), ImVec2{50.f, 50.f}))
                    {
                        std::cout << std::to_string((x * this->tailleGrid) + y) << "\n";
                    }
                    ImGui::PopID();
                    foundIt = true;
                }
            }
            for (cavalier piece : this->m_cavaliers.m_piecesListe)
            {
                if (piece.getPos() == Vec2<int>(x, y))
                {
                    ImGui::PushID((x * this->tailleGrid) + y);
                    if (ImGui::Button(piece.getName().c_str(), ImVec2{50.f, 50.f}))
                    {
                        std::cout << std::to_string((x * this->tailleGrid) + y) << "\n";
                    }
                    ImGui::PopID();
                    foundIt = true;
                }
            }
            for (fou piece : this->m_fous.m_piecesListe)
            {
                if (piece.getPos() == Vec2<int>(x, y))
                {
                    ImGui::PushID((x * this->tailleGrid) + y);
                    if (ImGui::Button(piece.getName().c_str(), ImVec2{50.f, 50.f}))
                    {
                        std::cout << std::to_string((x * this->tailleGrid) + y) << "\n";
                    }
                    ImGui::PopID();
                    foundIt = true;
                }
            }
            for (dame piece : this->m_dames.m_piecesListe)
            {
                if (piece.getPos() == Vec2<int>(x, y))
                {
                    ImGui::PushID((x * this->tailleGrid) + y);
                    if (ImGui::Button(piece.getName().c_str(), ImVec2{50.f, 50.f}))
                    {
                        std::cout << std::to_string((x * this->tailleGrid) + y) << "\n";
                    }
                    ImGui::PopID();
                    foundIt = true;
                }
            }
            for (roi piece : this->m_rois.m_piecesListe)
            {
                if (piece.getPos() == Vec2<int>(x, y))
                {
                    ImGui::PushID((x * this->tailleGrid) + y);
                    if (ImGui::Button(piece.getName().c_str(), ImVec2{50.f, 50.f}))
                    {
                        std::cout << std::to_string((x * this->tailleGrid) + y) << "\n";
                    }
                    ImGui::PopID();
                    foundIt = true;
                }
            }
            if (!foundIt)
            {
                ImGui::PushID((x * this->tailleGrid) + y);
                if (ImGui::Button(std::to_string((x * this->tailleGrid) + y).c_str(), ImVec2{50.f, 50.f}))
                {
                    std::cout << std::to_string((x * this->tailleGrid) + y) << "\n";
                }
                ImGui::PopID();
            }
        }
    }
}

void App::push_piece()
{
    for (int i{0}; i < 2 * this->tailleGrid; i++)
    {
        pion temp;
        if (i < this->tailleGrid)
            temp.setPos(Vec2<int>(i, 1));
        else
            temp.setPos(Vec2<int>(i - this->tailleGrid, this->tailleGrid - 2));
        this->m_pions.indiceChange = this->tailleGrid;
        this->m_pions.m_piecesListe.push_back(temp);
    }
    for (int i{0}; i < 4; i++)
    {
        tour temp;
        if (i < 2)
            temp.setPos(Vec2<int>((i == 0) ? 0 : this->tailleGrid - 1, 0));
        else
            temp.setPos(Vec2<int>((i == 2) ? 0 : this->tailleGrid - 1, this->tailleGrid - 1));
        this->m_tours.indiceChange = 2;

        this->m_tours.m_piecesListe.push_back(temp);

        cavalier temp2;
        if (i < 2)
            temp2.setPos(Vec2<int>((i == 0) ? 1 : this->tailleGrid - 2, 0));
        else
            temp2.setPos(Vec2<int>((i == 2) ? 1 : this->tailleGrid - 2, this->tailleGrid - 1));
        this->m_cavaliers.indiceChange = 2;
        this->m_cavaliers.m_piecesListe.push_back(temp2);

        fou temp3;
        if (i < 2)
            temp3.setPos(Vec2<int>((i == 0) ? 2 : this->tailleGrid - 3, 0));
        else
            temp3.setPos(Vec2<int>((i == 2) ? 2 : this->tailleGrid - 3, this->tailleGrid - 1));
        this->m_fous.indiceChange = 2;
        this->m_fous.m_piecesListe.push_back(temp3);
    }
    for (int i{0}; i < 2; i++)
    {
        dame temp;
        if (i < 1)
            temp.setPos(Vec2<int>(3, 0));
        else
            temp.setPos(Vec2<int>(3, this->tailleGrid - 1));
        this->m_dames.indiceChange = 1;
        this->m_dames.m_piecesListe.push_back(temp);

        roi temp2;
        if (i < 1)
            temp2.setPos(Vec2<int>(4, 0));
        else
            temp2.setPos(Vec2<int>(4, this->tailleGrid - 1));
        this->m_rois.indiceChange = 1;
        this->m_rois.m_piecesListe.push_back(temp2);
    }
}