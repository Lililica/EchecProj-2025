#include "tour.hpp"
#include <vector>

std::vector<std::pair<int, int>> tour::get_case_possible(std::vector<std::pair<int, int>> occuped_pos) const
{
    std::pair<int, int>              pos = get_pos();
    std::vector<std::pair<int, int>> case_possible;

    for (int i = 1; i < 8; i++)
    {
        if (pos.first + i < 8)
        {
            if (std::find(occuped_pos.begin(), occuped_pos.end(), std::pair<int, int>{pos.first + i, pos.second}) == occuped_pos.end())
                case_possible.emplace_back(pos.first + i, pos.second);
            else
                break;
        }
    }
    for (int i = 1; i < 8; i++)
    {
        if (pos.first - i >= 0)
        {
            if (std::find(occuped_pos.begin(), occuped_pos.end(), std::pair<int, int>{pos.first - i, pos.second}) == occuped_pos.end())
                case_possible.emplace_back(pos.first - i, pos.second);
            else
                break;
        }
    }
    for (int i = 1; i < 8; i++)
    {
        if (pos.second + i < 8)
        {
            if (std::find(occuped_pos.begin(), occuped_pos.end(), std::pair<int, int>{pos.first, pos.second + i}) == occuped_pos.end())
                case_possible.emplace_back(pos.first, pos.second + i);
            else
                break;
        }
    }
    for (int i = 1; i < 8; i++)
    {
        if (pos.second - i >= 0)
        {
            if (std::find(occuped_pos.begin(), occuped_pos.end(), std::pair<int, int>{pos.first, pos.second - i}) == occuped_pos.end())
                case_possible.emplace_back(pos.first, pos.second - i);
            else
                break;
        }
    }

    return case_possible;
}

std::vector<std::pair<int, int>> tour::get_attack_possible(std::vector<std::pair<int, int>> occuped_pos_ennemi, std::vector<std::pair<int, int>> occuped_pos_ally) const
{
    std::pair<int, int>              pos = get_pos();
    std::vector<std::pair<int, int>> attack_possible;

    for (int i = 1; i < 8; i++)
    {
        if (pos.first + i < 8)
        {
            if (std::find(occuped_pos_ally.begin(), occuped_pos_ally.end(), std::pair<int, int>{pos.first + i, pos.second}) != occuped_pos_ally.end())
                break;

            if (std::find(occuped_pos_ennemi.begin(), occuped_pos_ennemi.end(), std::pair<int, int>{pos.first + i, pos.second}) != occuped_pos_ennemi.end())
            {
                attack_possible.emplace_back(pos.first + i, pos.second);
                break;
            }
        }
    }
    for (int i = 1; i < 8; i++)
    {
        if (pos.first - i >= 0)
        {
            if (std::find(occuped_pos_ally.begin(), occuped_pos_ally.end(), std::pair<int, int>{pos.first - i, pos.second}) != occuped_pos_ally.end())
                break;

            if (std::find(occuped_pos_ennemi.begin(), occuped_pos_ennemi.end(), std::pair<int, int>{pos.first - i, pos.second}) != occuped_pos_ennemi.end())
            {
                attack_possible.emplace_back(pos.first - i, pos.second);
                break;
            }
        }
    }
    for (int i = 1; i < 8; i++)
    {
        if (pos.second + i < 8)
        {
            if (std::find(occuped_pos_ally.begin(), occuped_pos_ally.end(), std::pair<int, int>{pos.first, pos.second + i}) != occuped_pos_ally.end())
                break;

            if (std::find(occuped_pos_ennemi.begin(), occuped_pos_ennemi.end(), std::pair<int, int>{pos.first, pos.second + i}) != occuped_pos_ennemi.end())
            {
                attack_possible.emplace_back(pos.first, pos.second + i);
                break;
            }
        }
    }
    for (int i = 1; i < 8; i++)
    {
        if (pos.second - i >= 0)
        {
            if (std::find(occuped_pos_ally.begin(), occuped_pos_ally.end(), std::pair<int, int>{pos.first, pos.second - i}) != occuped_pos_ally.end())
                break;

            if (std::find(occuped_pos_ennemi.begin(), occuped_pos_ennemi.end(), std::pair<int, int>{pos.first, pos.second - i}) != occuped_pos_ennemi.end())
            {
                attack_possible.emplace_back(pos.first, pos.second - i);
                break;
            }
        }
    }

    return attack_possible;
}