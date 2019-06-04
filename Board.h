#ifndef BOARD
#define BOARD

#include <string>
#include <vector>
#include "corrdinate.h"
using namespace std;

static const int COLUMN = 8;
static const int ROW = 8;

class Board
{
private:
   int white_count, black_count;
   string board[ROW][COLUMN];
   string black_chip, white_chip, blank;
   bool full_board;
   vector<corrdinate> legal_play_spots;
   vector<corrdinate> reset_places, temp_chips;
   vector<vector<corrdinate> > chips_to_be_flipped;

public:
   Board();
   ~Board();
   Board(const Board& b);
   string get_chip(int row, int column);
   void display_board();
   void clean_board();
   void display_board(string ary[ROW][COLUMN]);
   bool is_black(string chip);
   bool is_white(string chip);
   bool is_free(string chip);
   void flip_chip(corrdinate corr);
   int get_black_score();
   int get_white_score();
   void get_scores();
   bool game_finished();
   void load_board();
   void legal_plys(bool player);
   void clear_board();
   void make_ply(corrdinate ply, bool player);
   void set_board_piece(corrdinate c, string x);
   vector<corrdinate>* get_possible_plys();
};

#include "Board.cpp"
#endif