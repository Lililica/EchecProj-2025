#include "board.hpp"

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
            temp.isOccuped = false;
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

void Board::calcul_content()
{
}

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