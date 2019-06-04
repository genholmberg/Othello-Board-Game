#ifndef GAME
#define GAME

#include <stdio.h>
#include "Board.h"
#include "corrdinate.h"

static const int STATIC_GAME_BOARD_EVAL[ROW][COLUMN] = {
    {120, -20, 20, 5, 5, 20, -20, 120},
    {-20, -40, -5, -5, -5, -5, -40, -20},
    {20, -5, 15, 3, 3, 15, -5, 20},
    {5, -5, 3, 3, 3, 3, -5, 5},
    {5, -5, 3, 3, 3, 3, -5, 5},
    {20, -5, 15, 3, 3, 15, -5, 20},
    {-20, -40, -5, -5, -5, -5, -40, -20},
    {120, -20, 20, 5, 5, 20, -20, 120}
};

class Game
{
   private:
      char AI, User;
      Board board;
      bool player;
      corrdinate make_play;

    public:
      Game();
      void get_winner();
      void play_game();
      corrdinate get_move();
      int min_alpha_beta (Board b, int alpha, int beta, int level, int depth);
      int max_alpha_beta (Board b, int alpha, int beta, int level, int depth);
      int SEF(Board b);
      int minimum(int v, int b);
      void load_board();
};

#include "Game.cpp"
#endif
