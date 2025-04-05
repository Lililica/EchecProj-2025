#pragma once

#include <cstdint>
#include <functional>
#include <vector>
#include "button.hpp"
#include "menuState.hpp"

class Menu {
private:
    MenuState state;

    std::vector<Button> _buttonList;

public:
    virtual ~Menu() = default;
    void change_menu(MenuState state);
    void draw_me();

    virtual void set_button() = 0;
    void         push_button(const Button& button) { _buttonList.push_back(button); };

    // void push_button(const std::string& name, std::pair<double, double> pos, std::pair<double, double> taille) { _buttonList.emplace_back(name, pos, taille); };

    MenuState get_state() const { return state; };
    void      set_state(MenuState state) { this->state = state; };
};