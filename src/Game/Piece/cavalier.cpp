#include "cavalier.hpp"
#include <vector>

std::vector<std::pair<int, int>> cavalier::get_case_possible(std::vector<std::pair<int, int>> occuped_pos) const
{
    std::pair<int, int>              pos = get_pos();
    std::vector<std::pair<int, int>> case_possible;

    if (pos.first + 2 < 8 && pos.second + 1 < 8)
    {
        if (std::find(occuped_pos.begin(), occuped_pos.end(), std::pair<int, int>{pos.first + 2, pos.second + 1}) == occuped_pos.end())
            case_possible.emplace_back(pos.first + 2, pos.second + 1);
    }
    if (pos.first + 2 < 8 && pos.second - 1 >= 0)
    {
        if (std::find(occuped_pos.begin(), occuped_pos.end(), std::pair<int, int>{pos.first + 2, pos.second - 1}) == occuped_pos.end())
            case_possible.emplace_back(pos.first + 2, pos.second - 1);
    }
    if (pos.first - 2 >= 0 && pos.second + 1 < 8)
    {
        if (std::find(occuped_pos.begin(), occuped_pos.end(), std::pair<int, int>{pos.first - 2, pos.second + 1}) == occuped_pos.end())
            case_possible.emplace_back(pos.first - 2, pos.second + 1);
    }
    if (pos.first - 2 >= 0 && pos.second - 1 >= 0)
    {
        if (std::find(occuped_pos.begin(), occuped_pos.end(), std::pair<int, int>{pos.first - 2, pos.second - 1}) == occuped_pos.end())
            case_possible.emplace_back(pos.first - 2, pos.second - 1);
    }
    if (pos.first + 1 < 8 && pos.second + 2 < 8)
    {
        if (std::find(occuped_pos.begin(), occuped_pos.end(), std::pair<int, int>{pos.first + 1, pos.second + 2}) == occuped_pos.end())
            case_possible.emplace_back(pos.first + 1, pos.second + 2);
    }
    if (pos.first + 1 < 8 && pos.second - 2 >= 0)
    {
        if (std::find(occuped_pos.begin(), occuped_pos.end(), std::pair<int, int>{pos.first + 1, pos.second - 2}) == occuped_pos.end())
            case_possible.emplace_back(pos.first + 1, pos.second - 2);
    }
    if (pos.first - 1 >= 0 && pos.second + 2 < 8)
    {
        if (std::find(occuped_pos.begin(), occuped_pos.end(), std::pair<int, int>{pos.first - 1, pos.second + 2}) == occuped_pos.end())
            case_possible.emplace_back(pos.first - 1, pos.second + 2);
    }
    if (pos.first - 1 >= 0 && pos.second - 2 >= 0)
    {
        if (std::find(occuped_pos.begin(), occuped_pos.end(), std::pair<int, int>{pos.first - 1, pos.second - 2}) == occuped_pos.end())
            case_possible.emplace_back(pos.first - 1, pos.second - 2);
    }

    return case_possible;
}

std::vector<std::pair<int, int>> cavalier::get_attack_possible(std::vector<std::pair<int, int>> occuped_pos_ennemi, std::vector<std::pair<int, int>> occuped_pos_ally) const
{
    std::pair<int, int>              pos = get_pos();
    std::vector<std::pair<int, int>> attack_possible;

    if (find(occuped_pos_ennemi.begin(), occuped_pos_ennemi.end(), std::pair<int, int>{pos.first + 2, pos.second + 1}) != occuped_pos_ennemi.end())
        attack_possible.emplace_back(pos.first + 2, pos.second + 1);
    if (find(occuped_pos_ennemi.begin(), occuped_pos_ennemi.end(), std::pair<int, int>{pos.first + 2, pos.second - 1}) != occuped_pos_ennemi.end())
        attack_possible.emplace_back(pos.first + 2, pos.second - 1);
    if (find(occuped_pos_ennemi.begin(), occuped_pos_ennemi.end(), std::pair<int, int>{pos.first - 2, pos.second + 1}) != occuped_pos_ennemi.end())
        attack_possible.emplace_back(pos.first - 2, pos.second + 1);
    if (find(occuped_pos_ennemi.begin(), occuped_pos_ennemi.end(), std::pair<int, int>{pos.first - 2, pos.second - 1}) != occuped_pos_ennemi.end())
        attack_possible.emplace_back(pos.first - 2, pos.second - 1);
    if (find(occuped_pos_ennemi.begin(), occuped_pos_ennemi.end(), std::pair<int, int>{pos.first + 1, pos.second + 2}) != occuped_pos_ennemi.end())
        attack_possible.emplace_back(pos.first + 1, pos.second + 2);
    if (find(occuped_pos_ennemi.begin(), occuped_pos_ennemi.end(), std::pair<int, int>{pos.first - 1, pos.second + 2}) != occuped_pos_ennemi.end())
        attack_possible.emplace_back(pos.first - 1, pos.second + 2);
    if (find(occuped_pos_ennemi.begin(), occuped_pos_ennemi.end(), std::pair<int, int>{pos.first + 1, pos.second - 2}) != occuped_pos_ennemi.end())
        attack_possible.emplace_back(pos.first + 1, pos.second - 2);
    if (find(occuped_pos_ennemi.begin(), occuped_pos_ennemi.end(), std::pair<int, int>{pos.first - 1, pos.second - 2}) != occuped_pos_ennemi.end())
        attack_possible.emplace_back(pos.first - 1, pos.second - 2);

    return attack_possible;
}