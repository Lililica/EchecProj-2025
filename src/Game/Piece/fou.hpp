#pragma once

#include <string>
#include "Game/Piece/piece.hpp"

class fou : public Piece {
private:
public:
    fou() = default;
    fou(PieceColor color, std::pair<int, int> pos, PieceType type)
        : Piece(color, pos, type) {};

    std::string name_for_imgui() const override { return get_color() == PieceColor::WHITE ? "b" : "n"; };
};