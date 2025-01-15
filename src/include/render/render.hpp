#pragma once

#include "../board/board.hpp"
#include "../pieces/piece.hpp"

struct RenderParameter {
    bool  foundIt;
    float itemSpacing  = 1.0f;
    bool  callAnUpdate = false;
};

class Render {
private:
    /* data */

    RenderParameter parameter;

    void check_pion(Board& board, int x, int y);
    void check_tour(Board& board, int x, int y);
    void check_cavalier(Board& board, int x, int y);
    void check_fou(Board& board, int x, int y);
    void check_dame(Board& board, int x, int y);
    void check_roi(Board& board, int x, int y);

protected:
public:
    void draw_content(Board& board);
    void draw_piece(int x, int y, const std::vector<piece>& pieces);
};
