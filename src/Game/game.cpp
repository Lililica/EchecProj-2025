#include "game.hpp"
#include <algorithm>
#include <iostream>
#include <vector>
#include "Game/Piece/piece.hpp"

void Game::select_piece(Piece* piece)
{
    SelectedPiece selectedPiece;
    selectedPiece.pos             = piece->get_pos();
    selectedPiece.piece           = piece;
    selectedPiece.case_possible   = piece->get_case_possible(get_occuped_pos(PieceColor::VOID));
    selectedPiece.attack_possible = piece->get_attack_possible(get_occuped_pos(piece->get_color() == PieceColor::WHITE ? PieceColor::BLACK : PieceColor::WHITE), get_occuped_pos(piece->get_color() == PieceColor::WHITE ? PieceColor::WHITE : PieceColor::BLACK));
    this->_selectedPiece          = selectedPiece;
}

void Game::piece_setup()
{
    // Pions
    _pions.clear();
    for (int i = 0; i < 8; i++)
    {
        _pions.emplace_back(PieceColor::WHITE, std::make_pair(i, 1), PieceType::PION);
        _pions.emplace_back(PieceColor::BLACK, std::make_pair(i, 6), PieceType::PION);
    }

    // Tours
    _tours.clear();
    for (int i = 0; i < 2; i++)
    {
        _tours.emplace_back(PieceColor::WHITE, std::make_pair(i * 7, 0), PieceType::TOUR);
        _tours.emplace_back(PieceColor::BLACK, std::make_pair(i * 7, 7), PieceType::TOUR);
    }

    // Fous
    _fous.clear();
    for (int i = 0; i < 2; i++)
    {
        _fous.emplace_back(PieceColor::WHITE, std::make_pair(3 * i + 2, 0), PieceType::FOU);
        _fous.emplace_back(PieceColor::BLACK, std::make_pair(3 * i + 2, 7), PieceType::FOU);
    }

    // Cavaliers
    _cavaliers.clear();
    for (int i = 0; i < 2; i++)
    {
        _cavaliers.emplace_back(PieceColor::WHITE, std::make_pair(1 + 5 * i, 0), PieceType::CAVALIER);
        _cavaliers.emplace_back(PieceColor::BLACK, std::make_pair(1 + 5 * i, 7), PieceType::CAVALIER);
    }

    // Dames
    _dames.clear();
    _dames.emplace_back(PieceColor::WHITE, std::make_pair(3, 0), PieceType::DAME);
    _dames.emplace_back(PieceColor::BLACK, std::make_pair(3, 7), PieceType::DAME);

    // Rois
    _rois.clear();
    _rois.emplace_back(PieceColor::WHITE, std::make_pair(4, 0), PieceType::ROI);
    _rois.emplace_back(PieceColor::BLACK, std::make_pair(4, 7), PieceType::ROI);
}

Piece* Game::get_piece(int x, int y)
{
    for (auto& pion : _pions)
    {
        if (pion.get_pos() == std::make_pair(x, y))
            return &pion;
    }

    for (auto& tour : _tours)
    {
        if (tour.get_pos() == std::make_pair(x, y))
            return &tour;
    }

    for (auto& fou : _fous)
    {
        if (fou.get_pos() == std::make_pair(x, y))
            return &fou;
    }

    for (auto& cavalier : _cavaliers)
    {
        if (cavalier.get_pos() == std::make_pair(x, y))
            return &cavalier;
    }

    for (auto& dame : _dames)
    {
        if (dame.get_pos() == std::make_pair(x, y))
            return &dame;
    }

    for (auto& roi : _rois)
    {
        if (roi.get_pos() == std::make_pair(x, y))
            return &roi;
    }

    return nullptr;
}

void Game::remove_piece(Piece* piece)
{
    if (piece->get_type() == PieceType::PION)
    {
        _pions.erase(std::remove_if(_pions.begin(), _pions.end(), [piece](const Pion& p) { return &p == piece; }), _pions.end());
    }
    else if (piece->get_type() == PieceType::TOUR)
    {
        _tours.erase(std::remove_if(_tours.begin(), _tours.end(), [piece](const tour& p) { return &p == piece; }), _tours.end());
    }
    else if (piece->get_type() == PieceType::FOU)
    {
        _fous.erase(std::remove_if(_fous.begin(), _fous.end(), [piece](const fou& p) { return &p == piece; }), _fous.end());
    }
    else if (piece->get_type() == PieceType::CAVALIER)
    {
        _cavaliers.erase(std::remove_if(_cavaliers.begin(), _cavaliers.end(), [piece](const cavalier& p) { return &p == piece; }), _cavaliers.end());
    }
    else if (piece->get_type() == PieceType::DAME)
    {
        _dames.erase(std::remove_if(_dames.begin(), _dames.end(), [piece](const dame& p) { return &p == piece; }), _dames.end());
    }
    else if (piece->get_type() == PieceType::ROI)
    {
        _rois.erase(std::remove_if(_rois.begin(), _rois.end(), [piece](const roi& p) { return &p == piece; }), _rois.end());
    }
}

void Game::move_piece(int x, int y)
{
    if (!_selectedPiece.has_value())
        return;

    // Verify you can go to this case
    auto possibleCase = _selectedPiece->case_possible;

    if (std::find(possibleCase.begin(), possibleCase.end(), std::make_pair(x, y)) == possibleCase.end() && std::find(_selectedPiece->attack_possible.begin(), _selectedPiece->attack_possible.end(), std::make_pair(x, y)) == _selectedPiece->attack_possible.end())
    {
        _selectedPiece.reset();
        return;
    }

    // If it is the same case, unselect the piece

    if (_selectedPiece->piece->get_pos() == std::make_pair(x, y))
    {
        _selectedPiece.reset();
        return;
    }

    auto* pieceSurLaCase = get_piece(x, y);

    if (pieceSurLaCase)
    {
        if (pieceSurLaCase->get_color() == _selectedPiece->piece->get_color())
        {
            _selectedPiece.reset();
            return;
        }
        auto possibleAttack = _selectedPiece->attack_possible;
        if (std::find(possibleAttack.begin(), possibleAttack.end(), std::make_pair(x, y)) != possibleAttack.end())
        {
            _selectedPiece->piece->set_pos(std::make_pair(x, y));
            if (pieceSurLaCase)
            {
                pieceSurLaCase->death();
                remove_piece(pieceSurLaCase);
            }
            _selectedPiece.reset();
            return;
        }
    }

    _selectedPiece->piece->set_pos(std::make_pair(x, y));
    if (pieceSurLaCase)
    {
        pieceSurLaCase->death();
        remove_piece(pieceSurLaCase);
    }
    _selectedPiece.reset();
}

std::vector<std::pair<int, int>> Game::get_occuped_pos(PieceColor color) const
{
    std::vector<std::pair<int, int>> pos;
    pos.reserve(_pions.size());

    auto add_positions = [&pos, color](const auto& pieces) {
        for (const auto& piece : pieces)
        {
            if (color == PieceColor::VOID || piece.get_color() == color)
            {
                pos.push_back(piece.get_pos());
            }
        }
    };

    add_positions(_pions);
    add_positions(_tours);
    add_positions(_fous);
    add_positions(_cavaliers);
    add_positions(_dames);
    add_positions(_rois);

    return pos;
}