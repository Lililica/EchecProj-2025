#pragma once

#include <memory>
#include <optional>
#include <utility>
#include <vector>
#include "Game/Piece/piece.hpp"
#include "board.hpp"

struct GameParameter {
    bool _isWhiteTurn{true};
    bool _isEndGame{false};
};

struct SelectedPiece {
    std::pair<int, int>              pos;
    Piece*                           piece;
    std::vector<std::pair<int, int>> case_possible;
    std::vector<std::pair<int, int>> attack_possible;
};

struct GestionEnPassant {
    bool                _thereIsEnPassant{false};
    std::vector<Piece*> _piecesEnPassantActive;
};

class Game {
private:
    GameParameter    _parameter;
    GestionEnPassant _gestionEnPassant;
    Board            _board{};

    std::vector<std::unique_ptr<Piece>> _pieces;

    std::optional<SelectedPiece> _selectedPiece{};

public:
    /*____________________ Constructors / Destructors ____________________*/
    virtual ~Game() = default;

    /*____________________ Game Gestion ____________________*/

    virtual void game_setup() = 0;
    void         piece_setup();
    void         select_piece(Piece* piece);
    void         move_piece(int x, int y);

    /*____________________ Inline Functions ____________________*/

    bool                             is_white_turn() const { return _parameter._isWhiteTurn; };
    void                             change_turn() { _parameter._isWhiteTurn = !_parameter._isWhiteTurn; };
    void                             reset_turn() { _parameter._isWhiteTurn = true; };
    bool                             get_isEndGame() const { return _parameter._isEndGame; };
    void                             reset_isEndGame() { _parameter._isEndGame = false; };
    int                              getGridSize() const { return _board._parameter.gridSize; };
    bool                             is_selected_piece() const { return _selectedPiece.has_value(); };
    std::pair<int, int>              get_pos_selected_piece() const { return _selectedPiece.has_value() ? _selectedPiece.value().pos : std::make_pair(-1, -1); };
    std::vector<std::pair<int, int>> get_possible_pos() const { return _selectedPiece.has_value() ? _selectedPiece.value().case_possible : std::vector<std::pair<int, int>>{}; };
    std::vector<std::pair<int, int>> get_attack_possible() const { return _selectedPiece.has_value() ? _selectedPiece.value().attack_possible : std::vector<std::pair<int, int>>{}; };

    /*____________________ UTILS ____________________*/

    void   remove_piece(Piece* piece);
    bool   check_if_end_game(Piece* pieceSurLaCase);
    Piece* get_piece(int x, int y);
    void   reset_en_passant();
    void   promote_pion(int x, int y);
    void   attack_en_passant(int x, int y);
    void   set_en_passant();
    void   move_if_rock(int x, int y);
};
