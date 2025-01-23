#include "board.hpp"
#include "include/pieces/pionUtils.hpp"

void Board::attribute_name_to_case(Case& temp, int x, int y)
{
    temp.pieceName = parameter.m_pions.setup_piece_to_case(x, y);
    if (temp.pieceName == "")
        temp.pieceName = parameter.m_tours.setup_piece_to_case(x, y);
    if (temp.pieceName == "")
        temp.pieceName = parameter.m_cavaliers.setup_piece_to_case(x, y);
    if (temp.pieceName == "")
        temp.pieceName = parameter.m_fous.setup_piece_to_case(x, y);
    if (temp.pieceName == "")
        temp.pieceName = parameter.m_dames.setup_piece_to_case(x, y);
    if (temp.pieceName == "")
        temp.pieceName = parameter.m_rois.setup_piece_to_case(x, y);

    temp.isPieceWhite = (temp.pieceName != "") ? is_cavalier_white(temp.pieceName) || is_dame_white(temp.pieceName) || is_pion_white(temp.pieceName) || is_roi_white(temp.pieceName) || is_tour_white(temp.pieceName) || is_fou_white(temp.pieceName) : false;
}

void Board::setup_case()
{
    for (int x{0}; x < parameter.tailleGrid; x++)
    {
        for (int y{0}; y < parameter.tailleGrid; y++)
        {
            Case temp;

            attribute_name_to_case(temp, x, y);

            temp.id        = (x * parameter.tailleGrid) + y;
            temp.isOccuped = temp.pieceName != "";
            temp.isWhite   = (x + y) % 2 == 0;
            temp.isActive  = temp.isPieceWhite;
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
    for (int i{0}; i < 2 * parameter.tailleGrid; i++)
    {
        pion temp;
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
        parameter.m_pions.indiceChange = parameter.tailleGrid;
        parameter.m_pions.m_piecesListe.push_back(temp);
    }
    for (int i{0}; i < 4; i++)
    {
        tour temp;
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
        parameter.m_tours.indiceChange = 2;

        parameter.m_tours.m_piecesListe.push_back(temp);

        cavalier temp2;
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
        parameter.m_cavaliers.indiceChange = 2;
        parameter.m_cavaliers.m_piecesListe.push_back(temp2);

        fou temp3;
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
        parameter.m_fous.indiceChange = 2;
        parameter.m_fous.m_piecesListe.push_back(temp3);
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
            temp.setPos(Vec2<int>(3, parameter.tailleGrid - 1));
            temp.setColorTeam(pieceColor::Black);
        }
        parameter.m_dames.indiceChange = 1;
        parameter.m_dames.m_piecesListe.push_back(temp);

        roi temp2;
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
        parameter.m_rois.indiceChange = 1;
        parameter.m_rois.m_piecesListe.push_back(temp2);
    }
}