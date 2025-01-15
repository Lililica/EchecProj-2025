#pragma once

#include <vector>
#include "../utils/utils.hpp"

template<typename T>
struct pieceConteneur {
    std::vector<T> m_piecesListe;

    int indiceChange;

    std::string setup_piece_to_case(int x, int y);
};

template<typename T>
std::string pieceConteneur<T>::setup_piece_to_case(int x, int y)
{
    for (auto& piece : m_piecesListe)
    {
        if (piece.getPos() == Vec2<int>{x, y})
            return piece.getName();
    }
    return "";
}