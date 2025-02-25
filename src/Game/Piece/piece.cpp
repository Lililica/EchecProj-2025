#include "piece.hpp"
#include <vector>

std::vector<std::pair<int, int>> get_occuped_pos(PieceColor color, const std::vector<std::unique_ptr<Piece>>& _pieces)
{
    std::vector<std::pair<int, int>> pos;
    pos.reserve(_pieces.size());

    for (const auto& piece : _pieces)
    {
        if (color == PieceColor::VOID || piece->get_color() == color)
        {
            pos.push_back(piece->get_pos());
        }
    }

    return pos;
}