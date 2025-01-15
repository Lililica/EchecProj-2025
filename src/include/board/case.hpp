#pragma once

#include <imgui.h>
#include <string>
#include "../utils/utils.hpp"

struct CaseColorList {
    // palette 1
    /*
        Rouge Foncé : #450920
        Rose Foncé : #A53860
        Rose : #DA627D
        Rose Pale : #FFA5AB
        Beige : #F9DBBD
    */

    Vec3<float> RougeFonce = from_hex_to_rgb("#450920");
    Vec3<float> RoseFonce  = from_hex_to_rgb("#A53860");
    Vec3<float> Rose       = from_hex_to_rgb("#DA627D");
    Vec3<float> RosePale   = from_hex_to_rgb("#FFA5AB");
    Vec3<float> Beige      = from_hex_to_rgb("#F9DBBD");

    ImVec4 colorWhiteCase       = ImVec4(RougeFonce.x, RougeFonce.y, RougeFonce.z, 1.0f);
    ImVec4 colorWhiteCase_hover = ImVec4(RosePale.x, RosePale.y, RosePale.z, 1.0f);
    ImVec4 colorBlackCase       = ImVec4(Rose.x, Rose.y, Rose.z, 1.0f);
    ImVec4 colorBlackCase_hover = ImVec4(RosePale.x, RosePale.y, RosePale.z, 1.0f);

    ImVec4 colorSelection       = ImVec4(0.4f, 0.7f, 0.0f, 1.0f);
    ImVec4 colorSelection_hover = ImVec4(0.3f, 0.6f, 0.0f, 1.0f);
};

struct Case {
    /* data */
    int id;

    bool isOccuped = false;
    bool isActive  = true;
    bool isWhite;
    bool isSelected = false;

    float size = 80.f;

    CaseColorList m_caseColor;

    ImVec4 color;
    ImVec4 color_hover;

    /* Piece information */
    std::string pieceName;

    void action(bool& callAnUpdate);
    void update_other_button();
};
