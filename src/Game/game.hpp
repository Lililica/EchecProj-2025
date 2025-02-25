#pragma once

#include <memory>
#include <optional>
#include <utility>
#include <vector>
#include "Game/Piece/piece.hpp"
#include "board.hpp"

struct GameParameter {
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
    GameParameter _parameter;
    Board         _board{};
    bool          _isWhiteTurn{true};
    bool          _isEndGame{false};

    GestionEnPassant _gestionEnPassant;

    std::vector<std::unique_ptr<Piece>> _pieces;

    // std::vector<Pion>     _pions;
    // std::vector<tour>     _tours;
    // std::vector<fou>      _fous;
    // std::vector<cavalier> _cavaliers;
    // std::vector<dame>     _dames;
    // std::vector<roi>      _rois;

    std::optional<SelectedPiece> _selectedPiece{};

public:
    int getGridSize() const { return _board._parameter.gridSize; };

    virtual ~Game()           = default;
    virtual void game_setup() = 0;

    void piece_setup();

    Piece*                           get_piece(int x, int y);
    void                             select_piece(Piece* piece);
    bool                             is_selected_piece() const { return _selectedPiece.has_value(); };
    void                             move_piece(int x, int y);
    void                             remove_piece(Piece* piece);
    std::vector<std::pair<int, int>> get_possible_pos() const { return _selectedPiece.has_value() ? _selectedPiece.value().case_possible : std::vector<std::pair<int, int>>{}; };
    std::vector<std::pair<int, int>> get_attack_possible() const { return _selectedPiece.has_value() ? _selectedPiece.value().attack_possible : std::vector<std::pair<int, int>>{}; };

    // std::vector<std::pair<int, int>> get_occuped_pos(PieceColor color) const;

    bool is_white_turn() const { return _isWhiteTurn; };
    void change_turn() { _isWhiteTurn = !_isWhiteTurn; };
    void reset_turn() { _isWhiteTurn = true; };
    bool get_isEndGame() const { return _isEndGame; };
    void reset_isEndGame() { _isEndGame = false; };

    std::pair<int, int> get_pos_selected_piece() const
    {
        return _selectedPiece.has_value() ? _selectedPiece.value().pos : std::make_pair(-1, -1);
    };
};
