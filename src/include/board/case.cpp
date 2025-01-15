#include "case.hpp"
#include <iostream>

void Case::action(bool& callAnUpdate)
{
    isSelected = !isSelected;
    if (isSelected)
    {
        this->color       = this->m_caseColor.colorSelection;
        this->color_hover = this->m_caseColor.colorSelection_hover;
        callAnUpdate      = true;
        isActive          = false;
    }
    else
    {
        this->color       = this->isWhite ? this->m_caseColor.colorWhiteCase : this->m_caseColor.colorBlackCase;
        this->color_hover = this->isWhite ? this->m_caseColor.colorWhiteCase_hover : this->m_caseColor.colorBlackCase_hover;
        callAnUpdate      = true;
        isActive          = false;
    }
    std::cout << this->pieceName << '\n';
}