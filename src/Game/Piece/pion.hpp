#pragma once

#include <string>
#include "piece.hpp"

class Pion : public Piece {
private:
public:
    Pion() = default;
    Pion(PieceColor color, std::pair<int, int> pos, PieceType type)
        : Piece(color, pos, type) {};

    std::string name_for_imgui() const override { return get_color() == PieceColor::WHITE ? "p" : "o"; };
};