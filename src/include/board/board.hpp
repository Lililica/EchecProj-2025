#pragma once
#include <imgui.h>
#include <vector>
#include "../pieces/piece.hpp"
#include "../pieces/pieceConteneur.hpp"
#include "case.hpp"

struct Board {
    int                      tailleGrid = 8;
    pieceConteneur<pion>     m_pions;
    pieceConteneur<tour>     m_tours;
    pieceConteneur<cavalier> m_cavaliers;
    pieceConteneur<fou>      m_fous;
    pieceConteneur<dame>     m_dames;
    pieceConteneur<roi>      m_rois;

    std::vector<Case> m_cases;

    void calcul_content();
    void setup_board();
    void push_piece();

    void attribute_name_to_case(Case& temp, int x, int y);
};