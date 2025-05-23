#pragma once

#include <string>
#include "Game/Piece/piece.hpp"

class tour : public Piece {
private:
    bool iCanRock = true;

public:
    tour() = default;
    tour(PieceColor color, std::pair<int, int> pos, PieceType type)
        : Piece(color, pos, type) {};

    bool get_iCanRock() const { return iCanRock; };
    void disable_iCanRock() { iCanRock = false; };

    std::string                      name_for_imgui() const override { return get_color() == PieceColor::BLACK ? "r" : "t"; };
    std::vector<std::pair<int, int>> get_case_possible(std::vector<std::unique_ptr<Piece>>& _pieces) const override;
    std::vector<std::pair<int, int>> get_attack_possible(std::vector<std::unique_ptr<Piece>>& _pieces) const override;
};