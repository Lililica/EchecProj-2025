#include "gameClassic.hpp"

void GameClassic::game_setup()
{
    // Classic game setup
    piece_setup();
    reset_isEndGame();
    reset_turn();
}
