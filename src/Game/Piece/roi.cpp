#include "roi.hpp"
#include <vector>

std::vector<std::pair<int, int>> roi::get_case_possible(std::vector<std::pair<int, int>> occuped_pos) const
{
    std::pair<int, int>              pos = get_pos();
    std::vector<std::pair<int, int>> case_possible;

    if (pos.first + 1 < 8 && pos.second + 1 < 8)
    {
        if (std::find(occuped_pos.begin(), occuped_pos.end(), std::pair<int, int>{pos.first + 1, pos.second + 1}) == occuped_pos.end())
            case_possible.emplace_back(pos.first + 1, pos.second + 1);
    }
    if (pos.first - 1 >= 0 && pos.second - 1 >= 0)
    {
        if (std::find(occuped_pos.begin(), occuped_pos.end(), std::pair<int, int>{pos.first - 1, pos.second - 1}) == occuped_pos.end())
            case_possible.emplace_back(pos.first - 1, pos.second - 1);
    }
    if (pos.first + 1 < 8 && pos.second - 1 >= 0)
    {
        if (std::find(occuped_pos.begin(), occuped_pos.end(), std::pair<int, int>{pos.first + 1, pos.second - 1}) == occuped_pos.end())
            case_possible.emplace_back(pos.first + 1, pos.second - 1);
    }
    if (pos.first - 1 >= 0 && pos.second + 1 < 8)
    {
        if (std::find(occuped_pos.begin(), occuped_pos.end(), std::pair<int, int>{pos.first - 1, pos.second + 1}) == occuped_pos.end())
            case_possible.emplace_back(pos.first - 1, pos.second + 1);
    }
    if (pos.first + 1 < 8)
    {
        if (std::find(occuped_pos.begin(), occuped_pos.end(), std::pair<int, int>{pos.first + 1, pos.second}) == occuped_pos.end())
            case_possible.emplace_back(pos.first + 1, pos.second);
    }
    if (pos.first - 1 >= 0)
    {
        if (std::find(occuped_pos.begin(), occuped_pos.end(), std::pair<int, int>{pos.first - 1, pos.second}) == occuped_pos.end())
            case_possible.emplace_back(pos.first - 1, pos.second);
    }
    if (pos.second + 1 < 8)
    {
        if (std::find(occuped_pos.begin(), occuped_pos.end(), std::pair<int, int>{pos.first, pos.second + 1}) == occuped_pos.end())
            case_possible.emplace_back(pos.first, pos.second + 1);
    }
    if (pos.second - 1 >= 0)
    {
        if (std::find(occuped_pos.begin(), occuped_pos.end(), std::pair<int, int>{pos.first, pos.second - 1}) == occuped_pos.end())
            case_possible.emplace_back(pos.first, pos.second - 1);
    }

    return case_possible;
}

std::vector<std::pair<int, int>> roi::get_attack_possible(std::vector<std::pair<int, int>> occuped_pos_ennemi, std::vector<std::pair<int, int>> occuped_pos_ally) const
{
    std::pair<int, int>              pos = get_pos();
    std::vector<std::pair<int, int>> attack_possible;

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