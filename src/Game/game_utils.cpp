#include "Game/Piece/dame.hpp"
#include "Game/Piece/pion.hpp"
#include "Game/Piece/roi.hpp"
#include "game.hpp"

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

bool Game::check_if_end_game(Piece* pieceSurLaCase)
{
    if (pieceSurLaCase->get_type() == PieceType::ROI)
    {
        this->_parameter._isEndGame = true;
        _selectedPiece.reset();
        for (auto& piece : _gestionEnPassant._piecesEnPassantActive)
        {
            Pion* pion = dynamic_cast<Pion*>(piece);
            pion->set_en_passant_droite(false);
            pion->set_en_passant_gauche(false);
        }
        _gestionEnPassant._piecesEnPassantActive.clear();
        _gestionEnPassant._thereIsEnPassant = false;
        return true;
    }
    return false;
}

void Game::reset_en_passant()
{
    for (auto& piece : _gestionEnPassant._piecesEnPassantActive)
    {
        Pion* pion = dynamic_cast<Pion*>(piece);
        pion->set_en_passant_droite(false);
        pion->set_en_passant_gauche(false);
    }
    _gestionEnPassant._piecesEnPassantActive.clear();
    _gestionEnPassant._thereIsEnPassant = false;
}

void Game::promote_pion(int x, int y)
{
    if (_selectedPiece->piece->get_type() == PieceType::PION && (y == 0 || y == 7))
    {
        _pieces.emplace_back(std::make_unique<dame>(_selectedPiece->piece->get_color(), std::make_pair(x, y), PieceType::DAME));
        _selectedPiece->piece->death();
        remove_piece(_selectedPiece->piece);
    }
}

void Game::attack_en_passant(int x, int y)
{
    Pion* pion = dynamic_cast<Pion*>(_selectedPiece->piece);
    if (pion->get_en_passant_droite() && x == pion->get_pos().first - 1 && y == pion->get_pos().second + (pion->get_color() == PieceColor::WHITE ? -1 : 1))
    {
        Piece* piece_ennemy = get_piece(pion->get_pos().first - 1, pion->get_pos().second);
        if (piece_ennemy && piece_ennemy->get_type() == PieceType::PION)
        {
            piece_ennemy->death();
            remove_piece(piece_ennemy);
        }
    }

    if (pion->get_en_passant_gauche() && x == pion->get_pos().first + 1 && y == pion->get_pos().second + (pion->get_color() == PieceColor::WHITE ? -1 : 1))
    {
        Piece* piece_ennemy = get_piece(pion->get_pos().first + 1, pion->get_pos().second);
        if (piece_ennemy && piece_ennemy->get_type() == PieceType::PION)
        {
            piece_ennemy->death();
            remove_piece(piece_ennemy);
        }
    }
}

void Game::set_en_passant()
{
    Pion* pion = dynamic_cast<Pion*>(_selectedPiece->piece);

    // piece 1
    Piece* piece_ennemy_1 = get_piece(_selectedPiece->pos.first + 1, _selectedPiece->pos.second + (_selectedPiece->piece->get_color() == PieceColor::WHITE ? -2 : 2));
    if (piece_ennemy_1 && piece_ennemy_1->get_type() == PieceType::PION)
    {
        Pion* pion_ennemy_1 = dynamic_cast<Pion*>(piece_ennemy_1);
        pion_ennemy_1->set_en_passant_gauche(true);
        _gestionEnPassant._thereIsEnPassant = true;
        _gestionEnPassant._piecesEnPassantActive.push_back(pion_ennemy_1);
    }
    // piece 2
    Piece* piece_ennemy_2 = get_piece(_selectedPiece->pos.first - 1, _selectedPiece->pos.second + (_selectedPiece->piece->get_color() == PieceColor::WHITE ? -2 : 2));
    if (piece_ennemy_2 && piece_ennemy_2->get_type() == PieceType::PION)
    {
        Pion* pion_ennemy_2 = dynamic_cast<Pion*>(piece_ennemy_2);
        pion_ennemy_2->set_en_passant_droite(true);
        _gestionEnPassant._thereIsEnPassant = true;
        _gestionEnPassant._piecesEnPassantActive.push_back(pion_ennemy_2);
    }
}

void Game::move_if_rock(int x, int y)
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