#include <iostream>
#include <string>
#include "corrdinate.h"
#include <cstring>
#include <fstream>
using namespace std;

Board::Board()
{
	white_count = 0;
	black_count = 0;
	full_board = false;
    /*black_chip = "\u26AB";
    white_chip = "\u26AA";
    blank = "U+1F35";*/
    black_chip = "B";
    white_chip = "W";
    blank = "O";
	clear_board();
}

Board::~Board()
{

}

Board::Board(const Board& b)
{
	this->white_count = b.white_count;
	this->black_count = b.black_count;
	this->full_board = b.full_board;
	for (int row = 0; row < ROW; row++)
	{
		for (int col = 0; col < COLUMN; col++)
		{
			this->board[row][col] = b.board[row][col];
		}
	}
	this->legal_play_spots = b.legal_play_spots;

	black_chip = "B";
	white_chip = "W";
	blank = "O";
}

string Board::get_chip(int row, int column)
{
	return board[row][column];
}

bool Board::is_black(string chip)
{
	if (chip == black_chip)
		return true;
	else
		return false;
}

bool Board::is_white(string chip)
{
	if (chip == white_chip)
		return true;
	else
		return false;
}

bool Board::is_free(string chip)
{
	if (chip != white_chip && chip != black_chip)
		return true;
	else
		return false;
}

void Board::display_board()
{
	cout << "  A B C D E F G H\n"; // take out
	for(int i = 0; i < ROW; i++)
	{
		cout  << i+1;  // take out
		for(int j = 0; j < COLUMN; j++)
			cout << " " << board[i][j];
		cout  << endl;
	}
	cout << endl;
}

void Board::flip_chip(corrdinate corr)
{
	if (board[corr.get_row()][corr.get_column()] == white_chip)
		board[corr.get_row()][corr.get_column()] = black_chip;
	else
		board[corr.get_row()][corr.get_column()] = white_chip;
}

void Board::clear_board()
{
	for(int i = 0; i < ROW; i++)
 	{
		for(int j = 0; j < COLUMN; j++)
			board[i][j] = blank;
	}
	board[3][3] = white_chip;
	board[4][4] = white_chip;
	board[3][4] = black_chip;
	board[4][3] = black_chip;
}

vector<corrdinate>* Board::get_possible_plys()
{
	return &legal_play_spots;
}

// Calculate scores for both white chips and black chips, sets bool if board is full
void Board::get_scores()
{
	white_count = 0;
	black_count = 0;
	for(int i = 0; i < ROW; i++)
	{
		for(int j = 0; j < COLUMN; j++)
		{
			if (is_white(board[i][j]))
				white_count++;
			else if (is_black(board[i][j]))
				black_count++;
		}
	}
	if (black_count + white_count == 64)
		full_board = true;
}

bool Board::game_finished()
{
	return full_board;
}

int Board::get_black_score()
{
	return black_count;
}

int Board::get_white_score()
{
	return white_count;
}

void Board::load_board()
{
	string file_name, line;
	int row = 0;
	cout << "What board do you want to load?\n";
	cin >> file_name;
	file_name = "Boards\\" + file_name;

	ifstream file(file_name.c_str());
	while (getline(file, line))
	{
		for(int col = 0; col < line.length(); col++)
		{
			board[row][col] = line[col];
		}
		row++;
	}
}

// Flips all chips that should be flipped given a ply.
void Board::make_ply(corrdinate p, bool player)
{
	string opp_piece, player_piece;
	corrdinate corr_flip, other_side, temp_corr;
	if (player)
	{
		opp_piece = white_chip;
		player_piece = black_chip;
	}
	else
	{
		opp_piece = black_chip;
		player_piece = white_chip;
	}

	// Find where they want to place their chip
	for (std::vector<corrdinate>::iterator it = legal_play_spots.begin(); it != legal_play_spots.end(); it++)
	{
		if (it->get_row() == p.get_row() && it->get_column() == p.get_column())
		{
			corr_flip.set_corrdinate(it->get_row(), it->get_column());
			if (player)
			{
				board[it->get_row()][it->get_column()] = black_chip;
			}
			else
			{
				board[it->get_row()][it->get_column()] = white_chip;
			}
		}
	}

	// Find player's chip on the right of the chip placed
	for(int c = corr_flip.get_column() + 1; c < COLUMN; c++)
	{
		// There is not a player chip to the right
		if(is_free(board[corr_flip.get_row()][c]))
		{
			break;
		}
		if (board[corr_flip.get_row()][c] == player_piece)
		{
			other_side.set_corrdinate(corr_flip.get_row(), c);
			for(int col = corr_flip.get_column() + 1; col < other_side.get_column(); col++)
			{
				temp_corr.set_corrdinate(corr_flip.get_row(), col);
				flip_chip(temp_corr);
			}
			break;
		}
	}
	// Find player's chip on the left of the chip placed
	for(int c = corr_flip.get_column() - 1; c >= 0; c--)
	{
		// There is not a player chip to the right
		if(is_free(board[corr_flip.get_row()][c]))
		{
			break;
		}
		if (board[corr_flip.get_row()][c] == player_piece)
		{
			other_side.set_corrdinate(corr_flip.get_row(), c);
			for(int col = corr_flip.get_column() - 1; col > other_side.get_column(); col--)
			{
				temp_corr.set_corrdinate(corr_flip.get_row(), col);
				flip_chip(temp_corr);
			}
			break;
		}
	}
	// Find player's chip on the above of the chip placed
	for(int r = corr_flip.get_row() - 1; r >= 0; r--)
	{
		// There is not a player chip to the right
		if(is_free(board[r][corr_flip.get_column()]))
		{
			break;
		}
		if (board[r][corr_flip.get_column()] == player_piece)
		{
			other_side.set_corrdinate(r, corr_flip.get_column());
			for(int row = corr_flip.get_row() - 1; row > other_side.get_row(); row--)
			{
				temp_corr.set_corrdinate(row, corr_flip.get_column());
				flip_chip(temp_corr);
			}
			break;
		}
	}
	// Find player's chip on the below of the chip placed
	for(int r = corr_flip.get_row() + 1; r < ROW; r++)
	{
		// There is not a player chip to the right
		if(is_free(board[r][corr_flip.get_column()]))
		{
			break;
		}
		if (board[r][corr_flip.get_column()] == player_piece)
		{
			other_side.set_corrdinate(r, corr_flip.get_column());
			for(int row = corr_flip.get_row() + 1; row < other_side.get_row(); row++)
			{
				temp_corr.set_corrdinate(row, corr_flip.get_column());
				flip_chip(temp_corr);
			}
			break;
		}
	}
	// Find player's chip on the right upper diagonal of the chip placed
	int ro, co;
	for (ro = corr_flip.get_row() - 1, co = corr_flip.get_column() + 1; ro >= 0 && co < COLUMN; ro--, co++)
	{
		// There is not a player chip to the right upper diagonal
		if(is_free(board[ro][co]))
		{
			break;
		}
		if (board[ro][co] == player_piece)
		{
			other_side.set_corrdinate(ro, co);
			int row, col;
			for(row = corr_flip.get_row() - 1, col = corr_flip.get_column() + 1; row > other_side.get_row() && col < other_side.get_column(); row--, col++)
			{
				temp_corr.set_corrdinate(row, col);
				flip_chip(temp_corr);
			}
			break;
		}
	}
	// Find player's chip on the right lower diagonal of the chip placed
	for (ro = corr_flip.get_row() + 1, co = corr_flip.get_column() - 1; ro < ROW && co >= 0; ro++, co--)
	{
		// There is not a player chip to the right
		if(is_free(board[ro][co]))
		{
			break;
		}
		if (board[ro][co] == player_piece)
		{
			other_side.set_corrdinate(ro, co);
			int row, col;
			for(row = corr_flip.get_row() + 1, col = corr_flip.get_column() - 1; row < other_side.get_row() && col > other_side.get_column(); row++, col--)
			{
				temp_corr.set_corrdinate(row, col);
				flip_chip(temp_corr);
			}
			break;
		}
	}
	// Find player's chip on the left lower diagonal of the chip placed
	for (ro = corr_flip.get_row() + 1, co = corr_flip.get_column() + 1; ro < ROW && co < COLUMN; ro++, co++)
	{
		// There is not a player chip to the right
		if(is_free(board[ro][co]))
		{
			break;
		}
		if (board[ro][co] == player_piece)
		{
			other_side.set_corrdinate(ro, co);
			int row, col;
			for(row = corr_flip.get_row() + 1, col = corr_flip.get_column() + 1; row < other_side.get_row() && col < other_side.get_column(); row++, col++)
			{
				temp_corr.set_corrdinate(row, col);
				flip_chip(temp_corr);
			}
			break;
		}
	}
	// Find player's chip on the left lower diagonal of the chip placed
	for (ro = corr_flip.get_row() - 1, co = corr_flip.get_column() - 1; ro >= 0 && co >= 0; ro--, co--)
	{
		// There is not a player chip to the right
		if(is_free(board[ro][co]))
		{
			break;
		}
		if (board[ro][co] == player_piece)
		{
			other_side.set_corrdinate(ro, co);
			int row, col;
			for(row = corr_flip.get_row() - 1, col = corr_flip.get_column() - 1; row > other_side.get_row() && col > other_side.get_column(); row--, col--)
			{
				temp_corr.set_corrdinate(row, col);
				flip_chip(temp_corr);
			}
			break;
		}
	}
	clean_board();
}

void Board::clean_board()
{
	int r, c;
	for(std::vector<corrdinate>::iterator it = legal_play_spots.begin(); it != legal_play_spots.end(); it++)
	{
		r = it->get_row();
		c = it->get_column();

		if (board[r][c] != blank && board[r][c] != white_chip && board[r][c] != black_chip)
		{
			board[r][c] = blank;
		}
	}
}

void Board::legal_plys(bool player)
{

	string legal_move = "L";
	string temp_board[ROW][COLUMN];
	legal_play_spots.clear();

	// makes a copy of the current game board
	copy(&board[0][0], &board[0][0] + ROW * COLUMN, &temp_board[0][0]);

	string opp_piece, player_piece;
	if (player)
	{
		opp_piece = white_chip;
		player_piece = black_chip;
	}
	else
	{
		opp_piece = black_chip;
		player_piece = white_chip;
	}
	for (int row = 0; row < ROW; row++)
	{
		for (int col = 0; col < COLUMN; col++)
		{
			bool player_piece_found = false;
			if (board[row][col] == player_piece)
			{
				player_piece_found = true;
			}

			if (player_piece_found)
			{

				//check for moves to the right horizontally
				bool cont = true;
				bool opp_piece_found = false;
				for (int i = col + 1; i < COLUMN; i++)
				{

					// A blank spot is the right, skip and move on
					if (board[row][i] == blank && !opp_piece_found)
					{
						cont = false;
						break;
					}

					// Checks if an opponent piece is found and continues
					if (board[row][i] == opp_piece && cont)
					{
						opp_piece_found = true;
						continue;
					}

					// Found same player piece and breaks out. e.i: two of the same color pieces next to each other
					else if (board[row][i] != opp_piece && board[row][i] != blank && cont)
					{
						break;
					}

					// Found a valid row/column to flip
					else if (board[row][i] == blank && opp_piece_found && cont)
					{
						temp_board[row][i] = legal_move;
						corrdinate temp_corr(row, i);
						legal_play_spots.push_back(temp_corr);
						break;
					}
				} // end of for

				//check moves to the left horizontally
				cont = true;
				opp_piece_found = false;
				for (int i = col - 1; i >= 0; i--)
				{

					// A blank spot is the right, skip and move on
					if (board[row][i] == blank && !opp_piece_found)
					{
						cont = false;
						break;
					}

					// Checks if an opponent piece is found and continues
					if (board[row][i] == opp_piece && cont)
					{
						opp_piece_found = true;
						continue;
					}

					// Found same player piece and breaks out. e.i: two of the same color pieces next to each other
					else if (board[row][i] != opp_piece && board[row][i] != blank && cont)
					{
						break;
					}

					// Found a valid row/column to flip
					else if (board[row][i] == blank && opp_piece_found && cont)
					{
						temp_board[row][i] = legal_move;
						corrdinate temp_corr(row, i);
						legal_play_spots.push_back(temp_corr);
						break;
					}
				} // end of for

				//check moves to the up vertically
				cont = true;
				opp_piece_found = false;
				for (int i = row - 1; i >= 0; i--)
				{

					// A blank spot is the right, skip and move on
					if (board[i][col] == blank && !opp_piece_found)
					{
						cont = false;
						break;
					}

					// Checks if an opponent piece is found and continues
					if (board[i][col] == opp_piece && cont)
					{
						opp_piece_found = true;
						continue;
					}

					// Found same player piece and breaks out. e.i: two of the same color pieces next to each other
					else if (board[i][col] != opp_piece && board[i][col] != blank && cont)
					{
						break;
					}

					// Found a valid row/column to flip
					else if (board[i][col] == blank && opp_piece_found && cont)
					{
						temp_board[i][col] = legal_move;
						corrdinate temp_corr(i, col);
						legal_play_spots.push_back(temp_corr);
						break;
					}
				} // end of for

				//check moves to the down vertically
				cont = true;
				opp_piece_found = false;
				for (int i = row + 1; i < ROW; i++)
				{

					// A blank spot is the right, skip and move on
					if (board[i][col] == blank && !opp_piece_found)
					{
						cont = false;
						break;
					}

					// Checks if an opponent piece is found and continues
					if (board[i][col] == opp_piece && cont)
					{
						opp_piece_found = true;
						continue;
					}

					// Found same player piece and breaks out. e.i: two of the same color pieces next to each other
					else if (board[i][col] != opp_piece && board[i][col] != blank && cont)
					{
						break;
					}

					// Found a valid row/column to flip
					else if (board[i][col] == blank && opp_piece_found && cont)
					{
						temp_board[i][col] = legal_move;
						corrdinate temp_corr(i, col);
						legal_play_spots.push_back(temp_corr);
						break;
					}
				} // end of for

				cont = true;
				opp_piece_found = false;
				int i, j;

				// Check upper right diagonally
				for (i = row - 1, j = col + 1; i >= 0 && j < COLUMN; i--, j++)
				{
					// A blank spot is the right, skip and move on
					if (board[i][j] == blank && !opp_piece_found)
					{
						cont = false;
						break;
					}

					// Checks if an opponent piece is found and continues
					if (board[i][j] == opp_piece && cont)
					{
						opp_piece_found = true;
						continue;
					}

					// Found same player piece and breaks out. e.i: two of the same color pieces next to each other
					else if (board[i][j] != opp_piece && board[i][j] != blank)
					{
						break;
					}

					// Found a valid row/column to flip
					else if (board[i][j] == blank && opp_piece_found)
					{
						temp_board[i][j] = legal_move;
						corrdinate temp_corr(i, j);
						legal_play_spots.push_back(temp_corr);
						break;
					}
				}

				cont = true;
				opp_piece_found = false;
				// Check lower right diagonally
				for (i = row + 1, j = col + 1; i < ROW && j < COLUMN; i++, j++)
				{
					// A blank spot is the right, skip and move on
					if (board[i][j] == blank && !opp_piece_found)
					{
						cont = false;
						break;
					}

					// Checks if an opponent piece is found and continues
					if (board[i][j] == opp_piece && cont)
					{
						opp_piece_found = true;
						continue;
					}

					// Found same player piece and breaks out. e.i: two of the same color pieces next to each other
					else if (board[i][j] != opp_piece && board[i][j] != blank)
					{
						break;
					}

					// Found a valid row/column to flip
					else if (board[i][j] == blank && opp_piece_found)
					{
						temp_board[i][j] = legal_move;
						corrdinate temp_corr(i, j);
						legal_play_spots.push_back(temp_corr);
						break;
					}
				}

				cont = true;
				opp_piece_found = false;
				// Check upper left diagonally
				for (i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--)
				{
					// A blank spot is the right, skip and move on
					if (board[i][j] == blank && !opp_piece_found)
					{
						cont = false;
						break;
					}

					// Checks if an opponent piece is found and continues
					if (board[i][j] == opp_piece && cont)
					{
						opp_piece_found = true;
						continue;
					}

					// Found same player piece and breaks out. e.i: two of the same color pieces next to each other
					else if (board[i][j] != opp_piece && board[i][j] != blank)
					{
						break;
					}

					// Found a valid row/column to flip
					else if (board[i][j] == blank && opp_piece_found)
					{
						temp_board[i][j] = legal_move;
						corrdinate temp_corr(i, j);
						legal_play_spots.push_back(temp_corr);
						break;
					}
				}

				cont = true;
				opp_piece_found = false;
				// Check lower left diagonally
				for (i = row + 1, j = col - 1; i < ROW && j >= 0; i++, j--)
				{
					// A blank spot is the right, skip and move on
					if (board[i][j] == blank && !opp_piece_found)
					{
						cont = false;
						break;
					}

					// Checks if an opponent piece is found and continues
					if (board[i][j] == opp_piece && cont)
					{
						opp_piece_found = true;
						continue;
					}

					// Found same player piece and breaks out. e.i: two of the same color pieces next to each other
					else if (board[i][j] != opp_piece && board[i][j] != blank)
					{
						break;
					}

					// Found a valid row/column to flip
					else if (board[i][j] == blank && opp_piece_found)
					{
						temp_board[i][j] = legal_move;
						corrdinate temp_corr(i, j);
						legal_play_spots.push_back(temp_corr);
						break;
					}
				}
			}	// player_piece_found if
		}	// column for loop
	}	// row for loop
	copy(&temp_board[0][0], &temp_board[0][0] + ROW * COLUMN, &board[0][0]);
}

void Board::display_board(string ary[][COLUMN])
{
	cout << "  A B C D E F G H\n"; // take out
	for (int i = 0; i < ROW; i++)
	{
		cout << i + 1; // take out
		for (int j = 0; j < COLUMN; j++)
			cout << " " << ary[i][j];
		cout << endl;
	}
	cout << endl;
}

void Board::set_board_piece(corrdinate c, string x)
{
	board[c.get_row()][c.get_column()] = x;
}
