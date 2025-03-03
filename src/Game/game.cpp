#include "game.hpp"
#include <algorithm>
#include <optional>
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
        _pieces.emplace_back(std::make_unique<Pion>(PieceColor::BLACK, std::make_pair(i, 1), PieceType::PION));
        _pieces.emplace_back(std::make_unique<Pion>(PieceColor::WHITE, std::make_pair(i, 6), PieceType::PION));
    }

    // Tours
    for (int i = 0; i < 2; i++)
    {
        _pieces.emplace_back(std::make_unique<tour>(PieceColor::BLACK, std::make_pair(i * 7, 0), PieceType::TOUR));
        _pieces.emplace_back(std::make_unique<tour>(PieceColor::WHITE, std::make_pair(i * 7, 7), PieceType::TOUR));
    }

    // Fous

    for (int i = 0; i < 2; i++)
    {
        _pieces.emplace_back(std::make_unique<fou>(PieceColor::BLACK, std::make_pair(3 * i + 2, 0), PieceType::FOU));
        _pieces.emplace_back(std::make_unique<fou>(PieceColor::WHITE, std::make_pair(3 * i + 2, 7), PieceType::FOU));
    }

    // Cavaliers
    for (int i = 0; i < 2; i++)
    {
        _pieces.emplace_back(std::make_unique<cavalier>(PieceColor::BLACK, std::make_pair(1 + 5 * i, 0), PieceType::CAVALIER));
        _pieces.emplace_back(std::make_unique<cavalier>(PieceColor::WHITE, std::make_pair(1 + 5 * i, 7), PieceType::CAVALIER));
    }

    // Dames
    _pieces.emplace_back(std::make_unique<dame>(PieceColor::BLACK, std::make_pair(3, 0), PieceType::DAME));
    _pieces.emplace_back(std::make_unique<dame>(PieceColor::WHITE, std::make_pair(3, 7), PieceType::DAME));

    // Rois
    _pieces.emplace_back(std::make_unique<roi>(PieceColor::BLACK, std::make_pair(4, 0), PieceType::ROI));
    _pieces.emplace_back(std::make_unique<roi>(PieceColor::WHITE, std::make_pair(4, 7), PieceType::ROI));
}

void Game::move_piece(int x, int y)
{
    // Check if a piece is selected

    if (!_selectedPiece.has_value())
        return;

    // Check if the move is possible

    auto possibleCase = _selectedPiece->case_possible;

    if (std::find(possibleCase.begin(), possibleCase.end(), std::make_pair(x, y)) == possibleCase.end() && std::find(_selectedPiece->attack_possible.begin(), _selectedPiece->attack_possible.end(), std::make_pair(x, y)) == _selectedPiece->attack_possible.end())
    {
        _selectedPiece.reset();
        return;
    }

    // Check if we are clicking on the same piece

    if (_selectedPiece->piece->get_pos() == std::make_pair(x, y))
    {
        _selectedPiece.reset();
        return;
    }

    // Check attack cases or moove cases

    /* ATTACK */

    auto* pieceSurLaCase = get_piece(x, y);

    if (pieceSurLaCase)
    {
        // Check if the piece is an enemy piece
        if (pieceSurLaCase->get_color() == _selectedPiece->piece->get_color())
        {
            _selectedPiece.reset();
            return;
        }

        // Check if the attack is possible
        std::vector<std::pair<int, int>> possibleAttack = _selectedPiece->attack_possible;
        if (std::find(possibleAttack.begin(), possibleAttack.end(), std::make_pair(x, y)) != possibleAttack.end())
        {
            if (_selectedPiece->piece->get_type() == PieceType::TOUR)
            {
                tour* tour = dynamic_cast<class tour*>(_selectedPiece->piece);
                tour->disable_iCanRock();
            }
            if (_selectedPiece->piece->get_type() == PieceType::ROI)
            {
                roi* roi = dynamic_cast<class roi*>(_selectedPiece->piece);
                roi->disable_isRockPossible();
            }
            _selectedPiece->piece->set_pos(std::make_pair(x, y));
            if (pieceSurLaCase)
            {
                if (check_if_end_game(pieceSurLaCase))
                    return;
                pieceSurLaCase->death();
                remove_piece(pieceSurLaCase);
            }
            _selectedPiece.reset();
            this->change_turn();
            reset_en_passant();
            promote_pion(x, y);
            return;
        }
    }

    /* MOOVE */

    if (_gestionEnPassant._thereIsEnPassant)
    {
        if (_selectedPiece->piece->get_type() == PieceType::PION)
            attack_en_passant(x, y);
        reset_en_passant();
    }

    if (_selectedPiece->piece->get_type() == PieceType::PION && _selectedPiece->piece->get_pos().second == 1 && y == 3)
        set_en_passant();

    if (_selectedPiece->piece->get_type() == PieceType::PION && _selectedPiece->piece->get_pos().second == 6 && y == 4)
        set_en_passant();

    if (_selectedPiece->piece->get_type() == PieceType::ROI)
    {
        roi* roi          = dynamic_cast<class roi*>(_selectedPiece->piece);
        bool tourAsMooved = false;
        if (roi->get_isRockPossible())
        {
            if (_selectedPiece->piece->get_color() == PieceColor::WHITE)
            {
                if (x == 2 && y == 7)
                    get_piece(0, 7)->set_pos(std::make_pair(3, 7));

                if (x == 6 && y == 7)
                    get_piece(7, 7)->set_pos(std::make_pair(5, 7));
            }
            if (_selectedPiece->piece->get_color() == PieceColor::BLACK)
            {
                if (x == 2 && y == 0)
                    get_piece(0, 0)->set_pos(std::make_pair(3, 0));

                if (x == 6 && y == 0)
                    get_piece(7, 0)->set_pos(std::make_pair(5, 0));
            }
        }

        roi->disable_isRockPossible();
    }

    if (_selectedPiece->piece->get_type() == PieceType::TOUR)
    {
        tour* tour = dynamic_cast<class tour*>(_selectedPiece->piece);
        tour->disable_iCanRock();
    }

    promote_pion(x, y);
    _selectedPiece->piece->set_pos(std::make_pair(x, y));
    this->change_turn();
    _selectedPiece.reset();
}