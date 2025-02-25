#pragma once

#include <string>
#include "Game/Piece/piece.hpp"

class dame : public Piece {
private:
public:
    dame() = default;
    dame(PieceColor color, std::pair<int, int> pos, PieceType type)
        : Piece(color, pos, type) {};

    std::string                      name_for_imgui() const override { return get_color() == PieceColor::WHITE ? "q" : "w"; };
    std::vector<std::pair<int, int>> get_case_possible(std::vector<std::unique_ptr<Piece>>& _pieces) const override;
    std::vector<std::pair<int, int>> get_attack_possible(std::vector<std::unique_ptr<Piece>>& _pieces) const override;
};