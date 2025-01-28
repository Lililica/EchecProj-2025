#include "board.hpp"
#include <iostream>

void Board::setup_board()
{
    push_piece();
    setup_case();
}

/*-----------------------------------------------------------------------------------------*/

void Board::calcul_content_game()
{
    if (parameter.update.isCallUpdateBoard())
    {
        if (!parameter.update.isInSelectionMode() && m_cases[parameter.update.callAnUpdate].isActive)
        {
            // Set the current selection to the case clicked
            parameter.update.currentSelectionPiece = parameter.update.callAnUpdate;

            // Give cases that we can access from the selected case
            parameter.update.updateList = give_right_id_after_selection(m_cases[parameter.update.currentSelectionPiece].pieceName, parameter.update.currentSelectionPiece);

            // Change parameter to all cases with updateList
            setup_parameter_and_color_for_accessible_cases();
        }
        else if (parameter.update.isInSelectionMode())
        {
            if (std::find(parameter.update.updateList.begin(), parameter.update.updateList.end(), parameter.update.callAnUpdate) != parameter.update.updateList.end())
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
        }

        parameter.update.callAnUpdate = -1;
    }
}

/*-----------------------------------------------------------------------------------------*/
