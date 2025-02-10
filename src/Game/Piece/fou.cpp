#include "fou.hpp"
#include <vector>

std::vector<std::pair<int, int>> fou::get_case_possible(std::vector<std::pair<int, int>> occuped_pos) const
{
    std::pair<int, int>              pos = get_pos();
    std::vector<std::pair<int, int>> case_possible;

    for (int i = 1; i < 8; i++)
    {
        if (pos.first + i < 8 && pos.second + i < 8)
        {
            if (std::find(occuped_pos.begin(), occuped_pos.end(), std::pair<int, int>{pos.first + i, pos.second + i}) == occuped_pos.end())
                case_possible.emplace_back(pos.first + i, pos.second + i);
            else
                break;
        }
    }
    for (int i = 1; i < 8; i++)
    {
        if (pos.first - i >= 0 && pos.second - i >= 0)
        {
            if (std::find(occuped_pos.begin(), occuped_pos.end(), std::pair<int, int>{pos.first - i, pos.second - i}) == occuped_pos.end())
                case_possible.emplace_back(pos.first - i, pos.second - i);
            else
                break;
        }
    }
    for (int i = 1; i < 8; i++)
    {
        if (pos.first + i < 8 && pos.second - i >= 0)
        {
            if (std::find(occuped_pos.begin(), occuped_pos.end(), std::pair<int, int>{pos.first + i, pos.second - i}) == occuped_pos.end())
                case_possible.emplace_back(pos.first + i, pos.second - i);
            else
                break;
        }
    }
    for (int i = 1; i < 8; i++)
    {
        if (pos.first - i >= 0 && pos.second + i < 8)
        {
            if (std::find(occuped_pos.begin(), occuped_pos.end(), std::pair<int, int>{pos.first - i, pos.second + i}) == occuped_pos.end())
                case_possible.emplace_back(pos.first - i, pos.second + i);
            else
                break;
        }
    }

    return case_possible;
}