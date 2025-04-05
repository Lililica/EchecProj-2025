#pragma once

#include <functional>
#include <string>
#include <utility>
#include "menuState.hpp"

struct Button {
    virtual ~Button() = default;
    std::string               name;
    std::pair<double, double> pos;
    std::pair<float, float>   taille;

    std::function<MenuState()> action;
};
