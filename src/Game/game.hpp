#pragma once

#include <optional>
#include <utility>
#include <vector>
#include "Game/Piece/cavalier.hpp"
#include "Game/Piece/dame.hpp"
#include "Game/Piece/fou.hpp"
#include "Game/Piece/piece.hpp"
#include "Game/Piece/pion.hpp"
#include "Game/Piece/roi.hpp"
#include "Game/Piece/tour.hpp"
#include "board.hpp"

struct GameParameter {
};

struct SelectedPiece {
    std::pair<int, int>              pos;
    Piece*                           piece;
    std::vector<std::pair<int, int>> case_possible;
};

class Game {
private:
    GameParameter _parameter;
    Board         _board{};

    std::vector<Pion>     _pions;
    std::vector<tour>     _tours;
    std::vector<fou>      _fous;
    std::vector<cavalier> _cavaliers;
    std::vector<dame>     _dames;
    std::vector<roi>      _rois;

    std::optional<SelectedPiece> _selectedPiece{};

public:
    int getGridSize() const { return _board._parameter.gridSize; };

    virtual ~Game()           = default;
    virtual void game_setup() = 0;

    void piece_setup();

    Piece*                           get_piece(int x, int y);
    void                             select_piece(Piece* piece) { _selectedPiece = SelectedPiece{.pos = piece->get_pos(), .piece = piece, .case_possible = piece->get_case_possible(get_occuped_pos())}; };
    bool                             is_selected_piece() const { return _selectedPiece.has_value(); };
    void                             move_piece(int x, int y);
    void                             remove_piece(Piece* piece);
    std::vector<std::pair<int, int>> get_possible_pos() const { return _selectedPiece.has_value() ? _selectedPiece.value().case_possible : std::vector<std::pair<int, int>>{}; };

    std::vector<std::pair<int, int>> get_occuped_pos() const;

    std::pair<int, int> get_pos_selected_piece() const
    {
        return _selectedPiece.has_value() ? _selectedPiece.value().pos : std::make_pair(-1, -1);
    };
};
