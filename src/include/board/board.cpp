#include "board.hpp"
#include <iostream>
#include "include/board/case.hpp"

void Board::setup_board()
{
    this->parameter.isWhitePlaying = true;
    push_piece();
    setup_case();
}

/*-----------------------------------------------------------------------------------------*/

void Board::calcul_content_game()
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
            }
            if (parameter.update.callAnUpdate != parameter.update.currentSelectionPiece)
            {
                m_cases[parameter.update.callAnUpdate].pieceName    = m_cases[parameter.update.currentSelectionPiece].pieceName;
                m_cases[parameter.update.callAnUpdate].isOccuped    = true;
                m_cases[parameter.update.callAnUpdate].isPieceWhite = true;
                m_cases[parameter.update.currentSelectionPiece].pieceName.clear();
                m_cases[parameter.update.currentSelectionPiece].isOccuped    = false;
                m_cases[parameter.update.currentSelectionPiece].isPieceWhite = false;
                parameter.update.currentSelectionPiece                       = -1;
                std::cout << "Piece moved at : " << parameter.update.callAnUpdate << '\n';

                this->parameter.isWhitePlaying = !this->parameter.isWhitePlaying;
                for (Case& c : m_cases)
                {
                    if (this->parameter.isWhitePlaying)
                    {
                        c.isActive = c.isOccuped && c.isPieceWhite;
                    }
                    else
                    {
                        c.isActive = c.isOccuped && !c.isPieceWhite;
                    }
                }
            }
            else
            {
                parameter.update.currentSelectionPiece = -1;
            }
        }
        // {
        // }

        parameter.update.callAnUpdate = -1;
    }
}

/*-----------------------------------------------------------------------------------------*/
