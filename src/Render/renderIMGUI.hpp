#pragma once

#include <imgui.h>
#include "Game/game.hpp"

struct RenderParameter {
    float spaceCase         = 1;
    float tailleCase        = 40;
    float taillePoliceChess = 50;
};

class RenderImGui {
private:
    RenderParameter parameter;

public:
    ImFont* ChessFont{};
    ImFont* DefaultFont{};

    void draw_content(Game& currentGame) const;
};