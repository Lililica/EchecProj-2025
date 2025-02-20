#pragma once

#include <cstdint>
#include <optional>
#include <utility>

enum class PieceColor : std::uint8_t { WHITE,
                                       BLACK,
                                       VOID };

enum class PieceType : std::uint8_t { PION,
                                      TOUR,
                                      FOU,
                                      CAVALIER,
                                      DAME,
                                      ROI };

struct PieceParameter {
    PieceColor                         pieceColor;
    std::optional<std::pair<int, int>> pos;
    PieceType                          pieceType;
};

class Game;

class Piece {
private:
    PieceParameter _parameter;

public:
    virtual ~Piece() = default;
    Piece()          = default;
    Piece(PieceColor color, std::pair<int, int> pos, PieceType type)
        : _parameter{.pieceColor = color, .pos = pos, .pieceType = type} {};

    void death() { _parameter.pos.reset(); };

    virtual std::string                      name_for_imgui() const                                                                                                            = 0;
    virtual std::vector<std::pair<int, int>> get_case_possible(std::vector<std::pair<int, int>> occuped_pos) const                                                             = 0;
    virtual std::vector<std::pair<int, int>> get_attack_possible(std::vector<std::pair<int, int>> occuped_pos_ennemi, std::vector<std::pair<int, int>> occuped_pos_ally) const = 0;

    PieceColor get_color() const
    {
        return _parameter.pieceColor;
    };
    std::pair<int, int> get_pos() const
    {
        return _parameter.pos.value();
    };
    void set_pos(std::pair<int, int> pos)
    {
        _parameter.pos = pos;
    };
    PieceType get_type() const
    {
        return _parameter.pieceType;
    };
};
