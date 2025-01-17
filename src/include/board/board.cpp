#include "board.hpp"
#include <iostream>

void Board::attribute_name_to_case(Case& temp, int x, int y)
{
    temp.pieceName = m_pions.setup_piece_to_case(x, y);
    if (temp.pieceName == "")
        temp.pieceName = m_tours.setup_piece_to_case(x, y);
    if (temp.pieceName == "")
        temp.pieceName = m_cavaliers.setup_piece_to_case(x, y);
    if (temp.pieceName == "")
        temp.pieceName = m_fous.setup_piece_to_case(x, y);
    if (temp.pieceName == "")
        temp.pieceName = m_dames.setup_piece_to_case(x, y);
    if (temp.pieceName == "")
        temp.pieceName = m_rois.setup_piece_to_case(x, y);
}

void Board::setup_board()
{
    push_piece();
    for (int x{0}; x < tailleGrid; x++)
    {
        for (int y{0}; y < tailleGrid; y++)
        {
            Case temp;

            attribute_name_to_case(temp, x, y);

            temp.id        = (x * tailleGrid) + y;
            temp.isOccuped = temp.pieceName != "";
            temp.isActive  = temp.isOccuped;
            temp.isWhite   = (x + y) % 2 == 0;
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

/*-----------------------------------------------------------------------------------------*/

std::vector<int> give_right_id_after_selection(std::string& pieceName, int& piece_id)
{
    std::vector<int> updateList{piece_id};

    Vec2 pos{piece_id % 8, piece_id / 8};

    // Pions

    if (pieceName == "o")
    {
        if (pos.x == 1)
        {
            updateList.push_back(piece_id + 1);
            updateList.push_back(piece_id + 2);
        }
        else
        {
            updateList.push_back(piece_id + 1);
        }
    }
    if (pieceName == "p")
    {
        if (pos.x == 6)
        {
            updateList.push_back(piece_id - 1);
            updateList.push_back(piece_id - 2);
        }
        else
        {
            updateList.push_back(piece_id - 2);
        }
    }

    // Roi

    if (pieceName == "w" || pieceName == "q")
    {
        if (pos.x == 0)
        {
            updateList.push_back(piece_id + 1);
            updateList.push_back(piece_id + 8);
            updateList.push_back(piece_id - 8);
            updateList.push_back(piece_id + 9);
            updateList.push_back(piece_id - 7);
        }
        else if (pos.x == 7)
        {
            updateList.push_back(piece_id - 1);
            updateList.push_back(piece_id + 8);
            updateList.push_back(piece_id - 8);
            updateList.push_back(piece_id - 9);
            updateList.push_back(piece_id + 7);
        }
        else
        {
            updateList.push_back(piece_id + 1);
            updateList.push_back(piece_id - 1);
            updateList.push_back(piece_id + 8);
            updateList.push_back(piece_id - 8);
            updateList.push_back(piece_id + 9);
            updateList.push_back(piece_id - 9);
            updateList.push_back(piece_id + 7);
            updateList.push_back(piece_id - 7);
        }
    }

    // Dame

    if (pieceName == "l" || pieceName == "k")
    {
        if (pos.x == 0)
        {
            updateList.push_back(piece_id + 1);
            updateList.push_back(piece_id + 8);
            updateList.push_back(piece_id - 8);
            updateList.push_back(piece_id + 9);
            updateList.push_back(piece_id - 7);
        }
        else if (pos.x == 7)
        {
            updateList.push_back(piece_id - 1);
            updateList.push_back(piece_id + 8);
            updateList.push_back(piece_id - 8);
            updateList.push_back(piece_id - 9);
            updateList.push_back(piece_id + 7);
        }
        else
        {
            updateList.push_back(piece_id + 1);
            updateList.push_back(piece_id - 1);
            updateList.push_back(piece_id + 8);
            updateList.push_back(piece_id - 8);
            updateList.push_back(piece_id + 9);
            updateList.push_back(piece_id - 9);
            updateList.push_back(piece_id + 7);
            updateList.push_back(piece_id - 7);
        }
        for (int i{2}; i < 8 - pos.x; i++)
            updateList.push_back(piece_id + i);
        for (int i{2}; i < pos.x + 1; i++)
            updateList.push_back(piece_id - i);
        for (int i{2}; i < 8 - pos.y; i++)
            updateList.push_back(piece_id + i * 8);
        for (int i{2}; i < pos.y + 1; i++)
            updateList.push_back(piece_id - i * 8);
        for (int i{2}; i < ((8 - pos.y) < (8 - pos.x) ? (8 - pos.y) : (8 - pos.x)); i++)
            updateList.push_back(piece_id + i * 9);
        for (int i{2}; i < ((pos.y + 1 < pos.x + 1) ? pos.y + 1 : pos.x + 1); i++)
            updateList.push_back(piece_id - i * 9);
        for (int i{2}; i < ((8 - pos.y) < (pos.x + 1) ? (8 - pos.y) : (pos.x + 1)); i++)
            updateList.push_back(piece_id + i * 7);
        for (int i{2}; i < ((pos.y + 1 < 8 - pos.x) ? pos.y + 1 : 8 - pos.x); i++)
            updateList.push_back(piece_id - i * 7);
    }

    // Fou

    if (pieceName == "n" || pieceName == "b")
    {
        for (int i{1}; i < ((8 - pos.y) < (8 - pos.x) ? (8 - pos.y) : (8 - pos.x)); i++)
            updateList.push_back(piece_id + i * 9);
        for (int i{1}; i < ((pos.y + 1 < pos.x + 1) ? pos.y + 1 : pos.x + 1); i++)
            updateList.push_back(piece_id - i * 9);
        for (int i{1}; i < ((8 - pos.y) < (pos.x + 1) ? (8 - pos.y) : (pos.x + 1)); i++)
            updateList.push_back(piece_id + i * 7);
        for (int i{1}; i < ((pos.y + 1 < 8 - pos.x) ? pos.y + 1 : 8 - pos.x); i++)
            updateList.push_back(piece_id - i * 7);
    }

    // Tour

    if (pieceName == "t" || pieceName == "r")
    {
        for (int i{1}; i < 8 - pos.x; i++)
            updateList.push_back(piece_id + i);
        for (int i{1}; i < pos.x + 1; i++)
            updateList.push_back(piece_id - i);
        for (int i{1}; i < 8 - pos.y; i++)
            updateList.push_back(piece_id + i * 8);
        for (int i{1}; i < pos.y + 1; i++)
            updateList.push_back(piece_id - i * 8);
    }

    // Cavalier

    if (pieceName == "j" || pieceName == "h")
    {
        if (pos.x == 0)
        {
            updateList.push_back(piece_id - 6);
            updateList.push_back(piece_id + 10);
            updateList.push_back(piece_id - 15);
            updateList.push_back(piece_id + 17);
        }
        else if (pos.x == 1)
        {
            updateList.push_back(piece_id - 6);
            updateList.push_back(piece_id + 10);
            updateList.push_back(piece_id - 15);
            updateList.push_back(piece_id - 17);
            updateList.push_back(piece_id + 15);
            updateList.push_back(piece_id + 17);
        }
        else if (pos.x == 6)
        {
            updateList.push_back(piece_id - 10);
            updateList.push_back(piece_id + 15);
            updateList.push_back(piece_id - 17);
            updateList.push_back(piece_id + 6);
            updateList.push_back(piece_id + 17);
            updateList.push_back(piece_id - 15);
        }
        else if (pos.x == 7)
        {
            updateList.push_back(piece_id - 10);
            updateList.push_back(piece_id + 15);
            updateList.push_back(piece_id - 17);
            updateList.push_back(piece_id + 6);
        }
        else
        {
            updateList.push_back(piece_id + 6);
            updateList.push_back(piece_id - 10);
            updateList.push_back(piece_id + 15);
            updateList.push_back(piece_id - 17);
            updateList.push_back(piece_id + 10);
            updateList.push_back(piece_id - 15);
            updateList.push_back(piece_id + 17);
            updateList.push_back(piece_id - 6);
        }
    }

    return updateList;
}

void Board::calcul_content()
{
    if (parameter.update.callAnUpdate != -1)
    {
        if (parameter.update.currentSelectionPiece == -1 && m_cases[parameter.update.callAnUpdate].isActive)
        {
            parameter.update.currentSelectionPiece = parameter.update.callAnUpdate;

            std::cout << "Call an update at piece : " << parameter.update.currentSelectionPiece << '\n';

            parameter.update.updateList = give_right_id_after_selection(m_cases[parameter.update.currentSelectionPiece].pieceName, parameter.update.currentSelectionPiece);
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
        else if (std::find(parameter.update.updateList.begin(), parameter.update.updateList.end(), parameter.update.callAnUpdate) != parameter.update.updateList.end())
        {
            if (parameter.update.callAnUpdate != parameter.update.currentSelectionPiece)
            {
                m_cases[parameter.update.callAnUpdate].pieceName = m_cases[parameter.update.currentSelectionPiece].pieceName;
                m_cases[parameter.update.callAnUpdate].isOccuped = true;
                m_cases[parameter.update.currentSelectionPiece].pieceName.clear();
                m_cases[parameter.update.currentSelectionPiece].isOccuped = false;
                parameter.update.currentSelectionPiece                    = -1;
                std::cout << "Piece moved at : " << parameter.update.callAnUpdate << '\n';
            }
            else
            {
                parameter.update.currentSelectionPiece = -1;
            }
            for (Case& c : m_cases)
            {
                if (c.isActive)
                {
                    if (c.isWhite)
                    {
                        c.color       = c.m_caseColor.colorWhiteCase;
                        c.color_hover = c.m_caseColor.colorWhiteCase_hover;
                    }
                    else
                    {
                        c.color       = c.m_caseColor.colorBlackCase;
                        c.color_hover = c.m_caseColor.colorBlackCase_hover;
                    }
                }
                c.isActive = c.isOccuped;
            }
        }
        // {
        // }

        parameter.update.callAnUpdate = -1;
    }
}

/*-----------------------------------------------------------------------------------------*/

void Board::push_piece()
{
    for (int i{0}; i < 2 * tailleGrid; i++)
    {
        pion temp;
        if (i < tailleGrid)
        {
            temp.setPos(Vec2<int>(i, 1));
            temp.setColorTeam(pieceColor::White);
        }
        else
        {
            temp.setPos(Vec2<int>(i - tailleGrid, tailleGrid - 2));
            temp.setColorTeam(pieceColor::Black);
        }
        m_pions.indiceChange = tailleGrid;
        m_pions.m_piecesListe.push_back(temp);
    }
    for (int i{0}; i < 4; i++)
    {
        tour temp;
        if (i < 2)
        {
            temp.setPos(Vec2<int>((i == 0) ? 0 : tailleGrid - 1, 0));
            temp.setColorTeam(pieceColor::White);
        }
        else
        {
            temp.setPos(Vec2<int>((i == 2) ? 0 : tailleGrid - 1, tailleGrid - 1));
            temp.setColorTeam(pieceColor::Black);
        }
        m_tours.indiceChange = 2;

        m_tours.m_piecesListe.push_back(temp);

        cavalier temp2;
        if (i < 2)
        {
            temp2.setPos(Vec2<int>((i == 0) ? 1 : tailleGrid - 2, 0));
            temp2.setColorTeam(pieceColor::White);
        }
        else
        {
            temp2.setPos(Vec2<int>((i == 2) ? 1 : tailleGrid - 2, tailleGrid - 1));
            temp2.setColorTeam(pieceColor::Black);
        }
        m_cavaliers.indiceChange = 2;
        m_cavaliers.m_piecesListe.push_back(temp2);

        fou temp3;
        if (i < 2)
        {
            temp3.setPos(Vec2<int>((i == 0) ? 2 : tailleGrid - 3, 0));
            temp3.setColorTeam(pieceColor::White);
        }
        else
        {
            temp3.setPos(Vec2<int>((i == 2) ? 2 : tailleGrid - 3, tailleGrid - 1));
            temp3.setColorTeam(pieceColor::Black);
        }
        m_fous.indiceChange = 2;
        m_fous.m_piecesListe.push_back(temp3);
    }
    for (int i{0}; i < 2; i++)
    {
        dame temp;
        if (i < 1)
        {
            temp.setPos(Vec2<int>(3, 0));
            temp.setColorTeam(pieceColor::White);
        }
        else
        {
            temp.setPos(Vec2<int>(3, tailleGrid - 1));
            temp.setColorTeam(pieceColor::Black);
        }
        m_dames.indiceChange = 1;
        m_dames.m_piecesListe.push_back(temp);

        roi temp2;
        if (i < 1)
        {
            temp2.setPos(Vec2<int>(4, 0));
            temp2.setColorTeam(pieceColor::White);
        }
        else
        {
            temp2.setPos(Vec2<int>(4, tailleGrid - 1));
            temp2.setColorTeam(pieceColor::Black);
        }
        m_rois.indiceChange = 1;
        m_rois.m_piecesListe.push_back(temp2);
    }
}