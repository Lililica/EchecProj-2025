#pragma once

#include <vector>
#include "include/utils/utils.hpp"

inline void mouve_pion_white(std::vector<int>& updateList, Vec2<int> pos, int& piece_id)
{
    if (pos.x == 1)
    {
        updateList.push_back(piece_id + 1);
        updateList.push_back(piece_id + 2);
    }
    else
    {
        updateList.push_back(piece_id + 1);
    }
}

inline void mouve_pion_black(std::vector<int>& updateList, Vec2<int> pos, int& piece_id)
{
    if (pos.x == 6)
    {
        updateList.push_back(piece_id - 1);
        updateList.push_back(piece_id - 2);
    }
    else
    {
        updateList.push_back(piece_id - 1);
    }
}

inline void mouve_roi(std::vector<int>& updateList, Vec2<int> pos, int& piece_id)
{
    if (pos.x == 0)
    {
        updateList.push_back(piece_id + 1);
        updateList.push_back(piece_id + 8);
        updateList.push_back(piece_id - 8);
        updateList.push_back(piece_id + 9);
        updateList.push_back(piece_id - 7);
    }
    else if (pos.x == 7)
    {
        updateList.push_back(piece_id - 1);
        updateList.push_back(piece_id + 8);
        updateList.push_back(piece_id - 8);
        updateList.push_back(piece_id - 9);
        updateList.push_back(piece_id + 7);
    }
    else
    {
        updateList.push_back(piece_id + 1);
        updateList.push_back(piece_id - 1);
        updateList.push_back(piece_id + 8);
        updateList.push_back(piece_id - 8);
        updateList.push_back(piece_id + 9);
        updateList.push_back(piece_id - 9);
        updateList.push_back(piece_id + 7);
        updateList.push_back(piece_id - 7);
    }
}

inline void mouve_dame(std::vector<int>& updateList, Vec2<int> pos, int& piece_id)
{
    if (pos.x == 0)
    {
        updateList.push_back(piece_id + 1);
        updateList.push_back(piece_id + 8);
        updateList.push_back(piece_id - 8);
        updateList.push_back(piece_id + 9);
        updateList.push_back(piece_id - 7);
    }
    else if (pos.x == 7)
    {
        updateList.push_back(piece_id - 1);
        updateList.push_back(piece_id + 8);
        updateList.push_back(piece_id - 8);
        updateList.push_back(piece_id - 9);
        updateList.push_back(piece_id + 7);
    }
    else
    {
        updateList.push_back(piece_id + 1);
        updateList.push_back(piece_id - 1);
        updateList.push_back(piece_id + 8);
        updateList.push_back(piece_id - 8);
        updateList.push_back(piece_id + 9);
        updateList.push_back(piece_id - 9);
        updateList.push_back(piece_id + 7);
        updateList.push_back(piece_id - 7);
    }
    for (int i{2}; i < 8 - pos.x; i++)
        updateList.push_back(piece_id + i);
    for (int i{2}; i < pos.x + 1; i++)
        updateList.push_back(piece_id - i);
    for (int i{2}; i < 8 - pos.y; i++)
        updateList.push_back(piece_id + i * 8);
    for (int i{2}; i < pos.y + 1; i++)
        updateList.push_back(piece_id - i * 8);
    for (int i{2}; i < ((8 - pos.y) < (8 - pos.x) ? (8 - pos.y) : (8 - pos.x)); i++)
        updateList.push_back(piece_id + i * 9);
    for (int i{2}; i < ((pos.y + 1 < pos.x + 1) ? pos.y + 1 : pos.x + 1); i++)
        updateList.push_back(piece_id - i * 9);
    for (int i{2}; i < ((8 - pos.y) < (pos.x + 1) ? (8 - pos.y) : (pos.x + 1)); i++)
        updateList.push_back(piece_id + i * 7);
    for (int i{2}; i < ((pos.y + 1 < 8 - pos.x) ? pos.y + 1 : 8 - pos.x); i++)
        updateList.push_back(piece_id - i * 7);
}

inline void mouve_fou(std::vector<int>& updateList, Vec2<int> pos, int& piece_id)
{
    for (int i{1}; i < ((8 - pos.y) < (8 - pos.x) ? (8 - pos.y) : (8 - pos.x)); i++)
        updateList.push_back(piece_id + i * 9);
    for (int i{1}; i < ((pos.y + 1 < pos.x + 1) ? pos.y + 1 : pos.x + 1); i++)
        updateList.push_back(piece_id - i * 9);
    for (int i{1}; i < ((8 - pos.y) < (pos.x + 1) ? (8 - pos.y) : (pos.x + 1)); i++)
        updateList.push_back(piece_id + i * 7);
    for (int i{1}; i < ((pos.y + 1 < 8 - pos.x) ? pos.y + 1 : 8 - pos.x); i++)
        updateList.push_back(piece_id - i * 7);
}

inline void mouve_tour(std::vector<int>& updateList, Vec2<int> pos, int& piece_id)
{
    for (int i{1}; i < 8 - pos.x; i++)
        updateList.push_back(piece_id + i);
    for (int i{1}; i < pos.x + 1; i++)
        updateList.push_back(piece_id - i);
    for (int i{1}; i < 8 - pos.y; i++)
        updateList.push_back(piece_id + i * 8);
    for (int i{1}; i < pos.y + 1; i++)
        updateList.push_back(piece_id - i * 8);
}

inline void mouve_cavalier(std::vector<int>& updateList, Vec2<int> pos, int& piece_id)
{
    if (pos.x == 0)
    {
        updateList.push_back(piece_id - 6);
        updateList.push_back(piece_id + 10);
        updateList.push_back(piece_id - 15);
        updateList.push_back(piece_id + 17);
    }
    else if (pos.x == 1)
    {
        updateList.push_back(piece_id - 6);
        updateList.push_back(piece_id + 10);
        updateList.push_back(piece_id - 15);
        updateList.push_back(piece_id - 17);
        updateList.push_back(piece_id + 15);
        updateList.push_back(piece_id + 17);
    }
    else if (pos.x == 6)
    {
        updateList.push_back(piece_id - 10);
        updateList.push_back(piece_id + 15);
        updateList.push_back(piece_id - 17);
        updateList.push_back(piece_id + 6);
        updateList.push_back(piece_id + 17);
        updateList.push_back(piece_id - 15);
    }
    else if (pos.x == 7)
    {
        updateList.push_back(piece_id - 10);
        updateList.push_back(piece_id + 15);
        updateList.push_back(piece_id - 17);
        updateList.push_back(piece_id + 6);
    }
    else
    {
        updateList.push_back(piece_id + 6);
        updateList.push_back(piece_id - 10);
        updateList.push_back(piece_id + 15);
        updateList.push_back(piece_id - 17);
        updateList.push_back(piece_id + 10);
        updateList.push_back(piece_id - 15);
        updateList.push_back(piece_id + 17);
        updateList.push_back(piece_id - 6);
    }
}
