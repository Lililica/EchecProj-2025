#pragma once

#include <string>
#include "Game/Piece/piece.hpp"

class tour : public Piece {
private:
public:
    tour() = default;
    tour(PieceColor color, std::pair<int, int> pos, PieceType type)
        : Piece(color, pos, type) {};

    std::string                      name_for_imgui() const override { return get_color() == PieceColor::WHITE ? "r" : "t"; };
    std::vector<std::pair<int, int>> get_case_possible(std::vector<std::pair<int, int>> occuped_pos) const override;
    std::vector<std::pair<int, int>> get_attack_possible(std::vector<std::pair<int, int>> occuped_pos_ennemi, std::vector<std::pair<int, int>> occuped_pos_ally) const override;
};