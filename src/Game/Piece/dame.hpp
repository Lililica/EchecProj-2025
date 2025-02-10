#pragma once

#include <string>
#include "Game/Piece/piece.hpp"

class dame : public Piece {
private:
public:
    dame() = default;
    dame(PieceColor color, std::pair<int, int> pos, PieceType type)
        : Piece(color, pos, type) {};

    std::string name_for_imgui() const override { return get_color() == PieceColor::WHITE ? "k" : "l"; };
};