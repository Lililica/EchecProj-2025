#pragma once

#include <cstdint>
#include <utility>

enum class PieceColor : std::uint8_t { WHITE,
                                       BLACK };

struct PieceParameter {
    PieceColor          pieceColor;
    std::pair<int, int> pos;
};

class Piece {
private:
    PieceParameter _parameter;

public:
};