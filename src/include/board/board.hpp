#pragma once
#include <imgui.h>
#include <vector>
#include "../pieces/piece.hpp"
#include "../pieces/pieceConteneur.hpp"
#include "case.hpp"

std::vector<int> give_right_id_after_selection(std::string& pieceName, int& piece_id);
void             setup_parameter_and_color_for_accessible_cases(Case& m_cases, std::vector<int>& updateList);

struct Update {
    std::vector<int> updateList;
    int              currentSelectionPiece = -1;
    int              callAnUpdate          = -1;

    bool isCallUpdateBoard() const { return callAnUpdate != -1; }
    bool isInSelectionMode() const { return currentSelectionPiece != -1; }
};

struct BoardParameter {
    Update update;

    int tailleGrid = 8;

    std::vector<piece> m_piece;
    // pieceConteneur<pion>     m_pions;
    // pieceConteneur<tour>     m_tours;
    // pieceConteneur<cavalier> m_cavaliers;
    // pieceConteneur<fou>      m_fous;
    // pieceConteneur<dame>     m_dames;
    // pieceConteneur<roi>      m_rois;

    ImFont* fontChess{};
};

struct Board {
    std::vector<Case> m_cases;

    BoardParameter parameter;

    void calcul_content_game();
    void setup_board();
    void setup_case();
    void push_piece();

    piece attribute_piece_to_case(int x, int y);
    void  setup_parameter_and_color_for_accessible_cases();
};
