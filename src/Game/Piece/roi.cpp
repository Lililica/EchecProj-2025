#include "roi.hpp"
#include <iostream>
#include <vector>
#include "Game/Piece/piece.hpp"
#include "Game/Piece/tour.hpp"

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

    /* ROCK Part */

    if (isRockPossible)
    {
        int nbrFreeCases = 0;
        if (get_color() == PieceColor::WHITE)
        {
            /* Grand roque */

            nbrFreeCases = 0;
            nbrFreeCases += std::find(occuped_pos.begin(), occuped_pos.end(), std::pair<int, int>{1, 7}) == occuped_pos.end();
            nbrFreeCases += std::find(occuped_pos.begin(), occuped_pos.end(), std::pair<int, int>{2, 7}) == occuped_pos.end();
            nbrFreeCases += std::find(occuped_pos.begin(), occuped_pos.end(), std::pair<int, int>{3, 7}) == occuped_pos.end();

            if (nbrFreeCases == 3)
            {
                for (auto& piece : _pieces)
                {
                    if (piece->get_pos() == std::pair<int, int>{0, 7} && piece->get_type() == PieceType::TOUR)
                    {
                        tour* tour = dynamic_cast<class tour*>(piece.get());
                        if (tour->get_iCanRock())
                            case_possible.emplace_back(2, 7);
                    }
                }
            }

            /* Petit roque */

            nbrFreeCases = 0;
            nbrFreeCases += std::find(occuped_pos.begin(), occuped_pos.end(), std::pair<int, int>{5, 7}) == occuped_pos.end();
            nbrFreeCases += std::find(occuped_pos.begin(), occuped_pos.end(), std::pair<int, int>{6, 7}) == occuped_pos.end();
            if (nbrFreeCases == 2)
            {
                for (auto& piece : _pieces)
                {
                    if (piece->get_pos() == std::pair<int, int>{7, 7} && piece->get_type() == PieceType::TOUR)
                    {
                        tour* tour = dynamic_cast<class tour*>(piece.get());
                        if (tour->get_iCanRock())
                            case_possible.emplace_back(6, 7);
                    }
                }
            }
        }
        if (get_color() == PieceColor::BLACK)
        {
            /* Grand roque */

            nbrFreeCases = 0;
            nbrFreeCases += std::find(occuped_pos.begin(), occuped_pos.end(), std::pair<int, int>{1, 0}) == occuped_pos.end();
            nbrFreeCases += std::find(occuped_pos.begin(), occuped_pos.end(), std::pair<int, int>{2, 0}) == occuped_pos.end();
            nbrFreeCases += std::find(occuped_pos.begin(), occuped_pos.end(), std::pair<int, int>{3, 0}) == occuped_pos.end();

            if (nbrFreeCases == 3)
            {
                for (auto& piece : _pieces)
                {
                    if (piece->get_pos() == std::pair<int, int>{7, 7} && piece->get_type() == PieceType::TOUR)
                    {
                        tour* tour = dynamic_cast<class tour*>(piece.get());
                        if (tour->get_iCanRock())
                            case_possible.emplace_back(2, 0);
                    }
                }
            }

            /* Petit roque */

            nbrFreeCases = 0;
            nbrFreeCases += std::find(occuped_pos.begin(), occuped_pos.end(), std::pair<int, int>{5, 0}) == occuped_pos.end();
            nbrFreeCases += std::find(occuped_pos.begin(), occuped_pos.end(), std::pair<int, int>{6, 0}) == occuped_pos.end();
            if (nbrFreeCases == 2)
            {
                for (auto& piece : _pieces)
                {
                    if (piece->get_pos() == std::pair<int, int>{7, 7} && piece->get_type() == PieceType::TOUR)
                    {
                        tour* tour = dynamic_cast<class tour*>(piece.get());
                        if (tour->get_iCanRock())
                            case_possible.emplace_back(6, 0);
                    }
                }
            }
        }
    }
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