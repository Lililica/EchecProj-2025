#include "roi.hpp"
#include <vector>

std::vector<std::pair<int, int>> roi::get_case_possible(std::vector<std::unique_ptr<Piece>>& _pieces) const
{
    std::pair<int, int>              pos = get_pos();
    std::vector<std::pair<int, int>> case_possible;

    std::vector<std::pair<int, int>> occuped_pos = get_occuped_pos(PieceColor::VOID, _pieces);

    auto add_case_if_valid = [&](int x, int y) {
        if (x >= 0 && x < 8 && y >= 0 && y < 8)
        {
            if (std::find(occuped_pos.begin(), occuped_pos.end(), std::pair<int, int>{x, y}) == occuped_pos.end())
            {
                case_possible.emplace_back(x, y);
            }
        }
    };

    add_case_if_valid(pos.first + 1, pos.second + 1);
    add_case_if_valid(pos.first - 1, pos.second - 1);
    add_case_if_valid(pos.first + 1, pos.second - 1);
    add_case_if_valid(pos.first - 1, pos.second + 1);
    add_case_if_valid(pos.first + 1, pos.second);
    add_case_if_valid(pos.first - 1, pos.second);
    add_case_if_valid(pos.first, pos.second + 1);
    add_case_if_valid(pos.first, pos.second - 1);

    return case_possible;
}

std::vector<std::pair<int, int>> roi::get_attack_possible(std::vector<std::unique_ptr<Piece>>& _pieces) const
{
    std::pair<int, int>              pos = get_pos();
    std::vector<std::pair<int, int>> attack_possible;

    std::vector<std::pair<int, int>> occuped_pos_ennemi = get_occuped_pos(get_color() == PieceColor::WHITE ? PieceColor::BLACK : PieceColor::WHITE, _pieces);
    std::vector<std::pair<int, int>> occuped_pos_ally   = get_occuped_pos(get_color() == PieceColor::BLACK ? PieceColor::BLACK : PieceColor::WHITE, _pieces);

    if (find(occuped_pos_ennemi.begin(), occuped_pos_ennemi.end(), std::pair<int, int>{pos.first + 1, pos.second - 1}) != occuped_pos_ennemi.end())
        attack_possible.emplace_back(pos.first + 1, pos.second - 1);
    if (find(occuped_pos_ennemi.begin(), occuped_pos_ennemi.end(), std::pair<int, int>{pos.first - 1, pos.second - 1}) != occuped_pos_ennemi.end())
        attack_possible.emplace_back(pos.first - 1, pos.second - 1);
    if (find(occuped_pos_ennemi.begin(), occuped_pos_ennemi.end(), std::pair<int, int>{pos.first + 1, pos.second + 1}) != occuped_pos_ennemi.end())
        attack_possible.emplace_back(pos.first + 1, pos.second + 1);
    if (find(occuped_pos_ennemi.begin(), occuped_pos_ennemi.end(), std::pair<int, int>{pos.first - 1, pos.second + 1}) != occuped_pos_ennemi.end())
        attack_possible.emplace_back(pos.first - 1, pos.second + 1);
    if (find(occuped_pos_ennemi.begin(), occuped_pos_ennemi.end(), std::pair<int, int>{pos.first + 1, pos.second}) != occuped_pos_ennemi.end())
        attack_possible.emplace_back(pos.first + 1, pos.second);
    if (find(occuped_pos_ennemi.begin(), occuped_pos_ennemi.end(), std::pair<int, int>{pos.first - 1, pos.second}) != occuped_pos_ennemi.end())
        attack_possible.emplace_back(pos.first - 1, pos.second);
    if (find(occuped_pos_ennemi.begin(), occuped_pos_ennemi.end(), std::pair<int, int>{pos.first, pos.second + 1}) != occuped_pos_ennemi.end())
        attack_possible.emplace_back(pos.first, pos.second + 1);
    if (find(occuped_pos_ennemi.begin(), occuped_pos_ennemi.end(), std::pair<int, int>{pos.first, pos.second - 1}) != occuped_pos_ennemi.end())
        attack_possible.emplace_back(pos.first, pos.second - 1);

    return attack_possible;
}