#pragma once

#include <imgui.h>
#include "Game/game.hpp"

struct RenderParameter {
    float spaceCase = 2;
};

class RenderImGui {
private:
    RenderParameter parameter;

public:
    ImFont* ChessFont{};
    ImFont* DefaultFont{};

    void draw_content(Game& currentGame) const;
};