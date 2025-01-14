#include "board.hpp"

void Board::setup_board()
{
    push_piece();
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
            temp.setPos(Vec2<int>(i, 1));
        else
            temp.setPos(Vec2<int>(i - tailleGrid, tailleGrid - 2));
        m_pions.indiceChange = tailleGrid;
        m_pions.m_piecesListe.push_back(temp);
    }
    for (int i{0}; i < 4; i++)
    {
        tour temp;
        if (i < 2)
            temp.setPos(Vec2<int>((i == 0) ? 0 : tailleGrid - 1, 0));
        else
            temp.setPos(Vec2<int>((i == 2) ? 0 : tailleGrid - 1, tailleGrid - 1));
        m_tours.indiceChange = 2;

        m_tours.m_piecesListe.push_back(temp);

        cavalier temp2;
        if (i < 2)
            temp2.setPos(Vec2<int>((i == 0) ? 1 : tailleGrid - 2, 0));
        else
            temp2.setPos(Vec2<int>((i == 2) ? 1 : tailleGrid - 2, tailleGrid - 1));
        m_cavaliers.indiceChange = 2;
        m_cavaliers.m_piecesListe.push_back(temp2);

        fou temp3;
        if (i < 2)
            temp3.setPos(Vec2<int>((i == 0) ? 2 : tailleGrid - 3, 0));
        else
            temp3.setPos(Vec2<int>((i == 2) ? 2 : tailleGrid - 3, tailleGrid - 1));
        m_fous.indiceChange = 2;
        m_fous.m_piecesListe.push_back(temp3);
    }
    for (int i{0}; i < 2; i++)
    {
        dame temp;
        if (i < 1)
            temp.setPos(Vec2<int>(3, 0));
        else
            temp.setPos(Vec2<int>(3, tailleGrid - 1));
        m_dames.indiceChange = 1;
        m_dames.m_piecesListe.push_back(temp);

        roi temp2;
        if (i < 1)
            temp2.setPos(Vec2<int>(4, 0));
        else
            temp2.setPos(Vec2<int>(4, tailleGrid - 1));
        m_rois.indiceChange = 1;
        m_rois.m_piecesListe.push_back(temp2);
    }
}