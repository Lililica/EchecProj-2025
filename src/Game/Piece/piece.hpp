#pragma once

#include <cstdint>
#include <memory>
#include <optional>
#include <utility>

enum class PieceColor : std::uint8_t { WHITE,
                                       BLACK,
                                       VOID };

enum PieceType { PION,
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

    void   death() { _parameter.pos.reset(); };
    Piece* get() { return this; }

    virtual std::string                      name_for_imgui() const                                                  = 0;
    virtual std::vector<std::pair<int, int>> get_case_possible(std::vector<std::unique_ptr<Piece>>& _pieces) const   = 0;
    virtual std::vector<std::pair<int, int>> get_attack_possible(std::vector<std::unique_ptr<Piece>>& _pieces) const = 0;

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

std::vector<std::pair<int, int>> get_occuped_pos(PieceColor color, const std::vector<std::unique_ptr<Piece>>& _pieces);