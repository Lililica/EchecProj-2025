#include <cstddef>
#include "board.hpp"
#include "case.hpp"
#include "include/pieces/piece.hpp"

piece Board::attribute_piece_to_case(int x, int y)
{
    for (piece& p : this->parameter.m_piece)
        if (p.getPos() == Vec2<int>{x, y})
            return p;

    piece pieceVide;
    pieceVide.setPos(Vec2<int>{x, y});
    pieceVide.setType(pieceType::Aucune);
    return pieceVide;
    // temp.pieceName = parameter.m_pions.setup_piece_to_case(x, y);
    // if (temp.pieceName == "")
    //     temp.pieceName = parameter.m_tours.setup_piece_to_case(x, y);
    // if (temp.pieceName == "")
    //     temp.pieceName = parameter.m_cavaliers.setup_piece_to_case(x, y);
    // if (temp.pieceName == "")
    //     temp.pieceName = parameter.m_fous.setup_piece_to_case(x, y);
    // if (temp.pieceName == "")
    //     temp.pieceName = parameter.m_dames.setup_piece_to_case(x, y);
    // if (temp.pieceName == "")
    //     temp.pieceName = parameter.m_rois.setup_piece_to_case(x, y);
}

void Board::setup_case()
{
    for (int x{0}; x < parameter.tailleGrid; x++)
    {
        for (int y{0}; y < parameter.tailleGrid; y++)
        {
            Case temp;

            temp.currentPiece = attribute_piece_to_case(x, y);

            temp.id        = (x * parameter.tailleGrid) + y;
            temp.m_pos     = Vec2<int>{x, y};
            temp.isOccuped = temp.currentPiece.getType() != pieceType::Aucune;

            temp.isActive = temp.isOccuped;
            temp.isWhite  = (x + y) % 2 == 0;
            if (temp.isWhite)
            {
                temp.color       = temp.m_caseColor.colorWhiteCase;
                temp.color_hover = temp.m_caseColor.colorWhiteCase_hover;
            }
            else
            {
                temp.color       = temp.m_caseColor.colorBlackCase;
                temp.color_hover = temp.m_caseColor.colorBlackCase_hover;
            }
            m_cases.push_back(temp);
        }
    }
}

void Board::push_piece()
{
    // pion
    for (int i{0}; i < 2 * parameter.tailleGrid; i++)
    {
        piece temp;
        if (i < parameter.tailleGrid)
        {
            temp.setPos(Vec2<int>(i, 1));
            temp.setColorTeam(pieceColor::White);
        }
        else
        {
            temp.setPos(Vec2<int>(i - parameter.tailleGrid, parameter.tailleGrid - 2));
            temp.setColorTeam(pieceColor::Black);
        }

        temp.setType(pieceType::Pion);
        // parameter.m_pions.indiceChange = parameter.tailleGrid;
        parameter.m_piece.push_back(temp);
    }

    for (int i{0}; i < 4; i++)
    {
        // Tour
        piece temp;
        if (i < 2)
        {
            temp.setPos(Vec2<int>((i == 0) ? 0 : parameter.tailleGrid - 1, 0));
            temp.setColorTeam(pieceColor::White);
        }
        else
        {
            temp.setPos(Vec2<int>((i == 2) ? 0 : parameter.tailleGrid - 1, parameter.tailleGrid - 1));
            temp.setColorTeam(pieceColor::Black);
        }
        // parameter.m_tours.indiceChange = 2;
        temp.setType(pieceType::Tour);
        parameter.m_piece.push_back(temp);

        // Cavalier
        piece temp2;
        if (i < 2)
        {
            temp2.setPos(Vec2<int>((i == 0) ? 1 : parameter.tailleGrid - 2, 0));
            temp2.setColorTeam(pieceColor::White);
        }
        else
        {
            temp2.setPos(Vec2<int>((i == 2) ? 1 : parameter.tailleGrid - 2, parameter.tailleGrid - 1));
            temp2.setColorTeam(pieceColor::Black);
        }
        // parameter.m_cavaliers.indiceChange = 2;
        temp2.setType(pieceType::Cavalier);
        parameter.m_piece.push_back(temp2);

        // Fou
        piece temp3;
        if (i < 2)
        {
            temp3.setPos(Vec2<int>((i == 0) ? 2 : parameter.tailleGrid - 3, 0));
            temp3.setColorTeam(pieceColor::White);
        }
        else
        {
            temp3.setPos(Vec2<int>((i == 2) ? 2 : parameter.tailleGrid - 3, parameter.tailleGrid - 1));
            temp3.setColorTeam(pieceColor::Black);
        }
        // parameter.m_fous.indiceChange = 2;
        temp3.setType(pieceType::Fou);
        parameter.m_piece.push_back(temp3);
    }
    for (int i{0}; i < 2; i++)
    {
        // Dame
        piece temp;
        if (i < 1)
        {
            temp.setPos(Vec2<int>(3, 0));
            temp.setColorTeam(pieceColor::White);
        }
        else
        {
            temp.setPos(Vec2<int>(3, parameter.tailleGrid - 1));
            temp.setColorTeam(pieceColor::Black);
        }
        // parameter.m_dames.indiceChange = 1;
        temp.setType(pieceType::Dame);
        parameter.m_piece.push_back(temp);

        // Roi
        piece temp2;
        if (i < 1)
        {
            temp2.setPos(Vec2<int>(4, 0));
            temp2.setColorTeam(pieceColor::White);
        }
        else
        {
            temp2.setPos(Vec2<int>(4, parameter.tailleGrid - 1));
            temp2.setColorTeam(pieceColor::Black);
        }
        // parameter.m_rois.indiceChange = 1;
        parameter.m_piece.push_back(temp2);
    }
}

void Board::setup_parameter_and_color_for_accessible_cases()
{
    for (Case& c : m_cases)
    {
        if (std::find(parameter.update.updateList.begin(), parameter.update.updateList.end(), c.id) != parameter.update.updateList.end())
        {
            c.isActive    = true;
            c.color       = c.m_caseColor.colorSelection;
            c.color_hover = c.m_caseColor.colorSelection_hover;
        }
        else
        {
            c.isActive = false;
        }
    }
}