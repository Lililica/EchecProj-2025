#pragma once

#include <imgui.h>
#include "../board/board.hpp"
#include "../pieces/piece.hpp"

struct RenderParameter {
    bool  foundIt;
    float itemSpacing  = 1.f;
    bool  callAnUpdate = false;
};

class Render {
private:
    /* data */

    RenderParameter parameter;

protected:
public:
    void draw_content(Board& board) const;
    void draw_piece(int x, int y, const std::vector<piece>& pieces);
};
