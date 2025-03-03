#pragma once

#include <string>
#include "piece.hpp"

class Pion : public Piece {
private:
    bool en_passant_droite = false;
    bool en_passant_gauche = false;

public:
    Pion() = default;
    Pion(PieceColor color, std::pair<int, int> pos, PieceType type)
        : Piece(color, pos, type) {};

    bool get_en_passant_droite() const { return en_passant_droite; };
    void set_en_passant_gauche(bool en_passant) { this->en_passant_droite = en_passant; };

    bool get_en_passant_gauche() const { return en_passant_gauche; };
    void set_en_passant_droite(bool en_passant) { this->en_passant_gauche = en_passant; };

    std::string                      name_for_imgui() const override { return get_color() == PieceColor::BLACK ? "p" : "o"; };
    std::vector<std::pair<int, int>> get_case_possible(std::vector<std::unique_ptr<Piece>>& _pieces) const override;
    std::vector<std::pair<int, int>> get_attack_possible(std::vector<std::unique_ptr<Piece>>& _pieces) const override;
};