#pragma once
#include <vector>
#include "piece.hpp"

template<typename T>
struct pieceConteneur {
    std::vector<T> m_piecesListe;
    int            indiceChange;
};

struct Board {
    int                      tailleGrid = 8;
    pieceConteneur<pion>     m_pions;
    pieceConteneur<tour>     m_tours;
    pieceConteneur<cavalier> m_cavaliers;
    pieceConteneur<fou>      m_fous;
    pieceConteneur<dame>     m_dames;
    pieceConteneur<roi>      m_rois;

    void calcul_content();
    void setup_board();
    void push_piece();
};