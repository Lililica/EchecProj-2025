#pragma once

#include <memory>
#include <vector>
#include "Game/Piece/_piece.hpp"
#include "board.hpp"

struct GameParameter {
};

class Game {
private:
    GameParameter _parameter;
    Board         _board;

    std::vector<std::unique_ptr<Piece>> _pieces;

public:
    int getGridSize() const { return _board._parameter.gridSize; };

    virtual ~Game()           = default;
    virtual void game_setup() = 0;
};
