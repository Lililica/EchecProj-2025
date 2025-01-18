#pragma once

#include <imgui.h>
#include <string>

struct Button {
    std::string m_name;
    int         m_id;
    ImVec4      m_color;
    std::string m_message;
};
