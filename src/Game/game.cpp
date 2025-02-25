#include "game.hpp"
#include <algorithm>
#include <iostream>
#include <vector>
#include "Game/Piece/cavalier.hpp"
#include "Game/Piece/dame.hpp"
#include "Game/Piece/fou.hpp"
#include "Game/Piece/piece.hpp"
#include "Game/Piece/pion.hpp"
#include "Game/Piece/roi.hpp"
#include "Game/Piece/tour.hpp"

void Game::select_piece(Piece* piece)
{
    SelectedPiece selectedPiece;
    selectedPiece.pos             = piece->get_pos();
    selectedPiece.piece           = piece;
    selectedPiece.case_possible   = piece->get_case_possible(_pieces);
    selectedPiece.attack_possible = piece->get_attack_possible(_pieces);
    this->_selectedPiece          = selectedPiece;
}

void Game::piece_setup()
{
    _pieces.clear();

    // Pions
    for (int i = 0; i < 8; i++)
    {
        _pieces.emplace_back(std::make_unique<Pion>(PieceColor::WHITE, std::make_pair(i, 1), PieceType::PION));
        _pieces.emplace_back(std::make_unique<Pion>(PieceColor::BLACK, std::make_pair(i, 6), PieceType::PION));
    }

    // Tours
    for (int i = 0; i < 2; i++)
    {
        _pieces.emplace_back(std::make_unique<tour>(PieceColor::WHITE, std::make_pair(i * 7, 0), PieceType::TOUR));
        _pieces.emplace_back(std::make_unique<tour>(PieceColor::BLACK, std::make_pair(i * 7, 7), PieceType::TOUR));
    }

    // Fous

    for (int i = 0; i < 2; i++)
    {
        _pieces.emplace_back(std::make_unique<fou>(PieceColor::WHITE, std::make_pair(3 * i + 2, 0), PieceType::FOU));
        _pieces.emplace_back(std::make_unique<fou>(PieceColor::BLACK, std::make_pair(3 * i + 2, 7), PieceType::FOU));
    }

    // Cavaliers
    for (int i = 0; i < 2; i++)
    {
        _pieces.emplace_back(std::make_unique<cavalier>(PieceColor::WHITE, std::make_pair(1 + 5 * i, 0), PieceType::CAVALIER));
        _pieces.emplace_back(std::make_unique<cavalier>(PieceColor::BLACK, std::make_pair(1 + 5 * i, 7), PieceType::CAVALIER));
    }

    // Dames
    _pieces.emplace_back(std::make_unique<dame>(PieceColor::WHITE, std::make_pair(3, 0), PieceType::DAME));
    _pieces.emplace_back(std::make_unique<dame>(PieceColor::BLACK, std::make_pair(3, 7), PieceType::DAME));

    // Rois
    _pieces.emplace_back(std::make_unique<roi>(PieceColor::WHITE, std::make_pair(4, 0), PieceType::ROI));
    _pieces.emplace_back(std::make_unique<roi>(PieceColor::BLACK, std::make_pair(4, 7), PieceType::ROI));
}

Piece* Game::get_piece(int x, int y)
{
    for (auto& piece : _pieces)
    {
        if (piece->get_pos() == std::make_pair(x, y))
            return piece.get();
    }

    return nullptr;
}

void Game::remove_piece(Piece* piece)
{
    _pieces.erase(std::remove_if(_pieces.begin(), _pieces.end(), [piece](const std::unique_ptr<Piece>& p) { return p.get() == piece; }), _pieces.end());
}

void Game::move_piece(int x, int y)
{
    if (!_selectedPiece.has_value())
        return;

    auto possibleCase = _selectedPiece->case_possible;

    if (std::find(possibleCase.begin(), possibleCase.end(), std::make_pair(x, y)) == possibleCase.end() && std::find(_selectedPiece->attack_possible.begin(), _selectedPiece->attack_possible.end(), std::make_pair(x, y)) == _selectedPiece->attack_possible.end())
    {
        _selectedPiece.reset();
        return;
    }

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
                if (pieceSurLaCase->get_type() == PieceType::ROI)
                {
                    this->_isEndGame = true;
                    _selectedPiece.reset();
                    for (auto& piece : _gestionEnPassant._piecesEnPassantActive)
                    {
                        Pion* pion = dynamic_cast<Pion*>(piece);
                        pion->set_en_passant_droite(false);
                        pion->set_en_passant_gauche(false);
                    }
                    _gestionEnPassant._piecesEnPassantActive.clear();
                    _gestionEnPassant._thereIsEnPassant = false;
                    return;
                }
                pieceSurLaCase->death();
                remove_piece(pieceSurLaCase);
            }
            _selectedPiece.reset();
            this->change_turn();
            for (auto& piece : _gestionEnPassant._piecesEnPassantActive)
            {
                Pion* pion = dynamic_cast<Pion*>(piece);
                pion->set_en_passant_droite(false);
                pion->set_en_passant_gauche(false);
            }
            if (_selectedPiece->piece->get_type() == PieceType::PION && y == 0 || y == 7)
            {
                _pieces.emplace_back(std::make_unique<dame>(_selectedPiece->piece->get_color(), std::make_pair(x, y), PieceType::DAME));
                _selectedPiece->piece->death();
                remove_piece(_selectedPiece->piece);
            }
            _gestionEnPassant._piecesEnPassantActive.clear();
            _gestionEnPassant._thereIsEnPassant = false;
            return;
        }
    }

    if (_gestionEnPassant._thereIsEnPassant)
    {
        if (_selectedPiece->piece->get_type() == PieceType::PION)
        {
            Pion* pion = dynamic_cast<Pion*>(_selectedPiece->piece);
            if (pion->get_en_passant_droite() && x == pion->get_pos().first - 1 && y == pion->get_pos().second + (pion->get_color() == PieceColor::BLACK ? -1 : 1))
            {
                Piece* piece_ennemy = get_piece(pion->get_pos().first - 1, pion->get_pos().second);
                if (piece_ennemy && piece_ennemy->get_type() == PieceType::PION)
                {
                    piece_ennemy->death();
                    remove_piece(piece_ennemy);
                }
            }

            if (pion->get_en_passant_gauche() && x == pion->get_pos().first + 1 && y == pion->get_pos().second + (pion->get_color() == PieceColor::BLACK ? -1 : 1))
            {
                Piece* piece_ennemy = get_piece(pion->get_pos().first + 1, pion->get_pos().second);
                if (piece_ennemy && piece_ennemy->get_type() == PieceType::PION)
                {
                    piece_ennemy->death();
                    remove_piece(piece_ennemy);
                }
            }
        }
        for (auto& piece : _gestionEnPassant._piecesEnPassantActive)
        {
            Pion* pion = dynamic_cast<Pion*>(piece);
            pion->set_en_passant_droite(false);
            pion->set_en_passant_gauche(false);
        }
        _gestionEnPassant._piecesEnPassantActive.clear();
        _gestionEnPassant._thereIsEnPassant = false;
    }

    if (_selectedPiece->piece->get_type() == PieceType::PION)
    {
        Pion* pion = dynamic_cast<Pion*>(_selectedPiece->piece);

        // piece 1
        Piece* piece_ennemy_1 = get_piece(_selectedPiece->pos.first + 1, _selectedPiece->pos.second + (_selectedPiece->piece->get_color() == PieceColor::BLACK ? -1 : 1));
        if (piece_ennemy_1 && piece_ennemy_1->get_type() == PieceType::PION)
        {
            Pion* pion_ennemy_1 = dynamic_cast<Pion*>(piece_ennemy_1);
            pion_ennemy_1->set_en_passant_gauche(true);
            _gestionEnPassant._thereIsEnPassant = true;
            _gestionEnPassant._piecesEnPassantActive.push_back(pion_ennemy_1);
        }
        // piece 2
        Piece* piece_ennemy_2 = get_piece(_selectedPiece->pos.first - 1, _selectedPiece->pos.second + (_selectedPiece->piece->get_color() == PieceColor::BLACK ? -1 : 1));
        if (piece_ennemy_2 && piece_ennemy_2->get_type() == PieceType::PION)
        {
            Pion* pion_ennemy_2 = dynamic_cast<Pion*>(piece_ennemy_2);
            pion_ennemy_2->set_en_passant_droite(true);
            _gestionEnPassant._thereIsEnPassant = true;
            _gestionEnPassant._piecesEnPassantActive.push_back(pion_ennemy_2);
        }
    }

    if (_selectedPiece->piece->get_type() == PieceType::PION && y == 0 || y == 7)
    {
        _pieces.emplace_back(std::make_unique<dame>(_selectedPiece->piece->get_color(), std::make_pair(x, y), PieceType::DAME));
        _selectedPiece->piece->death();
        remove_piece(_selectedPiece->piece);
    }

    _selectedPiece->piece->set_pos(std::make_pair(x, y));
    this->change_turn();
    _selectedPiece.reset();
}