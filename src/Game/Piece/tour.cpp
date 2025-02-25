#include "tour.hpp"
#include <vector>

std::vector<std::pair<int, int>> tour::get_case_possible(std::vector<std::unique_ptr<Piece>>& _pieces) const
{
    std::pair<int, int>              pos = get_pos();
    std::vector<std::pair<int, int>> case_possible;

    std::vector<std::pair<int, int>> occuped_pos = get_occuped_pos(PieceColor::VOID, _pieces);

    auto add_possible_moves = [&](int dx, int dy) {
        for (int i = 1; i < 8; i++)
        {
            int new_x = pos.first + i * dx;
            int new_y = pos.second + i * dy;
            if (new_x >= 0 && new_x < 8 && new_y >= 0 && new_y < 8)
            {
                if (std::find(occuped_pos.begin(), occuped_pos.end(), std::pair<int, int>{new_x, new_y}) == occuped_pos.end())
                    case_possible.emplace_back(new_x, new_y);
                else
                    break;
            }
        }
    };

    add_possible_moves(1, 0);
    add_possible_moves(-1, 0);
    add_possible_moves(0, 1);
    add_possible_moves(0, -1);

    return case_possible;
}

std::vector<std::pair<int, int>> tour::get_attack_possible(std::vector<std::unique_ptr<Piece>>& _pieces) const
{
    std::pair<int, int>              pos = get_pos();
    std::vector<std::pair<int, int>> attack_possible;

    std::vector<std::pair<int, int>> occuped_pos_ennemi = get_occuped_pos(get_color() == PieceColor::WHITE ? PieceColor::BLACK : PieceColor::WHITE, _pieces);
    std::vector<std::pair<int, int>> occuped_pos_ally   = get_occuped_pos(get_color() == PieceColor::BLACK ? PieceColor::BLACK : PieceColor::WHITE, _pieces);

    auto add_attack_moves = [&](int dx, int dy) {
        for (int i = 1; i < 8; i++)
        {
            int new_x = pos.first + i * dx;
            int new_y = pos.second + i * dy;
            if (new_x >= 0 && new_x < 8 && new_y >= 0 && new_y < 8)
            {
                if (std::find(occuped_pos_ally.begin(), occuped_pos_ally.end(), std::pair<int, int>{new_x, new_y}) != occuped_pos_ally.end())
                    break;

                if (std::find(occuped_pos_ennemi.begin(), occuped_pos_ennemi.end(), std::pair<int, int>{new_x, new_y}) != occuped_pos_ennemi.end())
                {
                    attack_possible.emplace_back(new_x, new_y);
                    break;
                }
            }
        }
    };

    add_attack_moves(1, 0);
    add_attack_moves(-1, 0);
    add_attack_moves(0, 1);
    add_attack_moves(0, -1);

    return attack_possible;
}