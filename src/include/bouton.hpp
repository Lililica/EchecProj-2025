#pragma once

#include "quick_imgui/quick_imgui.hpp"

class button {
private:
    int    m_id;
    ImVec4 m_color;

public:
    explicit button(int& id)
        : m_id(id) {
        };
    button(button& b);
    ~button() = default;
};