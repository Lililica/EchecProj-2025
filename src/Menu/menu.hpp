#pragma once

#include <cstdint>
#include <vector>
#include "button.hpp"

enum class MenuState : std::uint8_t { HOME,
                                      IN_GAME,
                                      PAUSE,
                                      PARAMETER };

class Menu {
private:
    MenuState state;

    std::vector<Button> _buttonList;

public:
    void change_menu(MenuState state);
};