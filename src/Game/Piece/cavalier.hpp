#pragma once

#include <string>
#include "Game/Piece/piece.hpp"

class cavalier : public Piece {
private:
public:
    cavalier() = default;
    cavalier(PieceColor color, std::pair<int, int> pos, PieceType type)
        : Piece(color, pos, type) {};

    std::string                      name_for_imgui() const override { return get_color() == PieceColor::WHITE ? "h" : "j"; };
    std::vector<std::pair<int, int>> get_case_possible(std::vector<std::pair<int, int>> occuped_pos) const override;
};