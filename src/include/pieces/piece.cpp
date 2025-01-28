#include "piece.hpp"

std::string piece::getName() const
{
    switch (m_type)
    {
    case pieceType::Pion:
        if (m_colorTeam == pieceColor::White)
            return "o";
        else if (m_colorTeam == pieceColor::Black)
            return "p";
        return "Pion";
    case pieceType::Cavalier:
        if (m_colorTeam == pieceColor::White)
            return "j";
        else if (m_colorTeam == pieceColor::Black)
            return "h";
        return "Cavalier";
    case pieceType::Fou:
        if (m_colorTeam == pieceColor::White)
            return "n";
        else if (m_colorTeam == pieceColor::Black)
            return "b";
        return "Fou";
    case pieceType::Tour:
        if (m_colorTeam == pieceColor::White)
            return "t";
        else if (m_colorTeam == pieceColor::Black)
            return "r";
        return "Tour";
    case pieceType::Dame:
        if (m_colorTeam == pieceColor::White)
            return "l";
        else if (m_colorTeam == pieceColor::Black)
            return "k";
        return "Dame";
    case pieceType::Roi:
        if (m_colorTeam == pieceColor::White)
            return "w";
        else if (m_colorTeam == pieceColor::Black)
            return "q";
        return "Roi";
    }
}