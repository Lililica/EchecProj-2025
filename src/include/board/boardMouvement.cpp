#include "boardMouvement.hpp"
#include <iostream>
#include "../pieces/pionUtils.hpp"
#include "board.hpp"

std::vector<int> give_right_id_after_selection(std::string& pieceName, int& piece_id)
{
    std::vector<int> updateList{piece_id};

    Vec2 pos{piece_id % 8, piece_id / 8};

    // Pions

    if (is_pion_white(pieceName))
        mouve_pion_white(updateList, pos, piece_id);

    if (is_pion_black(pieceName))
        mouve_pion_black(updateList, pos, piece_id);

    // Roi

    if (is_roi(pieceName))
        mouve_roi(updateList, pos, piece_id);

    // Dame

    if (is_dame(pieceName))
        mouve_dame(updateList, pos, piece_id);

    // Fou

    if (is_fou(pieceName))
        mouve_fou(updateList, pos, piece_id);

    // Tour

    if (is_tour(pieceName))
        mouve_tour(updateList, pos, piece_id);

    // Cavalier

    if (is_cavalier(pieceName))
        mouve_cavalier(updateList, pos, piece_id);

    return updateList;
}
