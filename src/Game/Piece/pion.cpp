#include "pion.hpp"
#include <vector>

std::vector<std::pair<int, int>> Pion::get_case_possible(std::vector<std::unique_ptr<Piece>>& _pieces) const
{
    std::pair<int, int>              pos = get_pos();
    std::vector<std::pair<int, int>> case_possible;

    std::vector<std::pair<int, int>> occuped_pos = get_occuped_pos(PieceColor::VOID, _pieces);

    if (get_color() == PieceColor::WHITE)
    {
        if (pos.second == 6)
        {
            bool firstEmpty = std::find(occuped_pos.begin(), occuped_pos.end(), std::pair<int, int>{pos.first, pos.second - 1}) == occuped_pos.end();
            if (firstEmpty)
                case_possible.emplace_back(pos.first, pos.second - 1);

            if (std::find(occuped_pos.begin(), occuped_pos.end(), std::pair<int, int>{pos.first, pos.second - 2}) == occuped_pos.end() && firstEmpty)
                case_possible.emplace_back(pos.first, pos.second - 2);
        }
        else
        {
            if (std::find(occuped_pos.begin(), occuped_pos.end(), std::pair<int, int>{pos.first, pos.second - 1}) == occuped_pos.end())
                case_possible.emplace_back(pos.first, pos.second - 1);
        }
    }
    else
    {
        if (pos.second == 1)
        {
            bool firstEmpty = std::find(occuped_pos.begin(), occuped_pos.end(), std::pair<int, int>{pos.first, pos.second + 1}) == occuped_pos.end();
            if (firstEmpty)
                case_possible.emplace_back(pos.first, pos.second + 1);

            if (std::find(occuped_pos.begin(), occuped_pos.end(), std::pair<int, int>{pos.first, pos.second + 2}) == occuped_pos.end() && firstEmpty)
                case_possible.emplace_back(pos.first, pos.second + 2);
        }
        else
        {
            if (std::find(occuped_pos.begin(), occuped_pos.end(), std::pair<int, int>{pos.first, pos.second + 1}) == occuped_pos.end())
                case_possible.emplace_back(pos.first, pos.second + 1);
        }
    }

    return case_possible;
}

std::vector<std::pair<int, int>> Pion::get_attack_possible(std::vector<std::unique_ptr<Piece>>& _pieces) const
{
    std::pair<int, int>              pos = get_pos();
    std::vector<std::pair<int, int>> attack_possible;

    std::vector<std::pair<int, int>> occuped_pos_ennemi = get_occuped_pos(get_color() == PieceColor::WHITE ? PieceColor::BLACK : PieceColor::WHITE, _pieces);
    std::vector<std::pair<int, int>> occuped_pos_ally   = get_occuped_pos(get_color() == PieceColor::BLACK ? PieceColor::BLACK : PieceColor::WHITE, _pieces);

    if (get_color() == PieceColor::WHITE)
    {
        if (find(occuped_pos_ennemi.begin(), occuped_pos_ennemi.end(), std::pair<int, int>{pos.first + 1, pos.second - 1}) != occuped_pos_ennemi.end())
            attack_possible.emplace_back(pos.first + 1, pos.second - 1);
        if (find(occuped_pos_ennemi.begin(), occuped_pos_ennemi.end(), std::pair<int, int>{pos.first - 1, pos.second - 1}) != occuped_pos_ennemi.end())
            attack_possible.emplace_back(pos.first - 1, pos.second - 1);
        if (get_en_passant_droite())
        {
            attack_possible.emplace_back(pos.first - 1, pos.second - 1);
        }
        if (get_en_passant_gauche())
        {
            attack_possible.emplace_back(pos.first + 1, pos.second - 1);
        }
    }
    else
    {
        if (find(occuped_pos_ennemi.begin(), occuped_pos_ennemi.end(), std::pair<int, int>{pos.first + 1, pos.second + 1}) != occuped_pos_ennemi.end())
            attack_possible.emplace_back(pos.first + 1, pos.second + 1);
        if (find(occuped_pos_ennemi.begin(), occuped_pos_ennemi.end(), std::pair<int, int>{pos.first - 1, pos.second + 1}) != occuped_pos_ennemi.end())
            attack_possible.emplace_back(pos.first - 1, pos.second + 1);
        if (get_en_passant_droite())
        {
            attack_possible.emplace_back(pos.first - 1, pos.second + 1);
        }
        if (get_en_passant_gauche())
        {
            attack_possible.emplace_back(pos.first + 1, pos.second + 1);
        }
    }

    return attack_possible;
}
