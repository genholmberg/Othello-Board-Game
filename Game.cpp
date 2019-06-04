// AI is false for player
// human is true for player
#include "Game.h"
#include <iostream>
#include <stdlib.h>
#include <string>
#include <climits>
using namespace std;

Game::Game()
{
	Board board;
	board.clear_board();
}

void Game::get_winner()
{
	board.get_scores();

	if (board.get_white_score() < board.get_black_score())
		printf("Player One wins!\n");
	else if (board.get_white_score() > board.get_black_score())
		printf("Player Two wins!\n");
	else
		printf("It's a draw!\n");
}

corrdinate Game::get_move()
{
 	int row, col;
 	char column;
 	corrdinate answer;
 	cout << "Enter your move,\nEnter the row then the column with a space between them: (e.i.: 3 E)";
 	cin >> row >> column;
 	col = column - '@';
    //cout << "\nDebug get_move() row: " << row << " column " << column; // take out
 	answer.set_corrdinate(row - 1, col - 1); // row - 1 because an array starts at 0
 	return answer;
}

// to do finish AI part of loop of game
void Game::play_game()
{
	bool player;
	int level = 1, depth = 3, choice = 0;
	cout << "Enter 1 if you want to be Player 1\n"
		 << "Enter 2 if you want to be Player 2.\n";

	while (choice != 1 && choice !=2)
	{
		cin >> choice;
		if (choice == 1)
		{
			player = true;
			User = 'B';
			AI = 'W';

		}
		else if (choice == 2)
		{
			player = false;
			AI = 'B';
			User = 'W';
		}
		else
		{
			cout << "Invalid input, please try again.\n";
		}
	}

	while (board.game_finished() == false)
	{
		board.get_scores();
		// Player
		board.legal_plys(player);
		cout << "\nPlayer 1's Score: " << board.get_black_score() << "\nPlayer 2's Score: " << board.get_white_score() << endl;
		board.display_board();
		if (player)
		{
			board.make_ply(get_move(), player);
		}
		board.get_scores();
		player = true;

		//AI
		int move_value = INT_MIN;
		// cout << "Move value is before the for loop:  	" << move_value << endl;
		corrdinate best_ply;
		board.legal_plys(!player);
		vector<corrdinate> *_plys = board.get_possible_plys();
		for (std::vector<corrdinate>::iterator it = _plys->begin(); it != _plys->end(); it++)
		{
			// cout << "legal move corr [r, c]:[ " << it->get_row() << ", " << it->get_column() << "]" << endl;
			// create a new board be implementing the play
			Board copy_current_board(board);
			// cout << "legal move set" << endl;
			copy_current_board.legal_plys(!player);
			// copy_current_board.display_board();
			// cout << "where is the move" << endl;
			// copy_current_board.set_board_piece(*it, "X");
			// copy_current_board.display_board();
			// copy_current_board.set_board_piece(*it, "L");
			copy_current_board.make_ply(*it, !player);
			int value = min_alpha_beta(copy_current_board, INT_MIN, INT_MAX, level, depth);
			// cout << "after value" << endl << "move value: " << move_value << endl << "value : " << value << endl;
			if (value > move_value)
			{
				//cout << "Play that is made corr [r, c]:[ " << it->get_row() << ", " << it->get_column() << "]" << endl;
				move_value = value;
				it->set_play_value(move_value);
				board.make_ply(*it, !player);
				// board.display_board();
			}
		}
		board.get_scores();
	}
	get_winner();
}

void Game::load_board()
{
	board.load_board();
	cout << "Board loaded in:\n";
	board.display_board();
}

// to do finish minimax
int Game::min_alpha_beta (Board b, int alpha, int beta, int level, int depth)
{
	int v;
	Board temp_board(b);
	vector<corrdinate>* possible_plys = b.get_possible_plys();

	if (level == depth)
		return SEF(temp_board);
	if (temp_board.game_finished())
	{
		// The AI won
		if(AI == 'W')
		{
			if (temp_board.get_white_score() > temp_board.get_black_score())
			{
				return (temp_board.get_white_score() - temp_board.get_black_score());
			}
			else // Draw
			{
				return 0;
			}
		}
		if(AI == 'B')
		{
			if (temp_board.get_black_score() > temp_board.get_white_score())
			{
				return (temp_board.get_black_score() - temp_board.get_white_score());
			}
			else // Draw
			{
				return 0;
			}
		}
	}
	for (std::vector<corrdinate>::iterator it = possible_plys->begin(); it != possible_plys->end(); it++)
	{
		temp_board.make_ply(*it, true);
		v = max_alpha_beta (temp_board, alpha, beta, level+1, depth);
		// reset board - do I need to if it is a copy?
		beta = minimum(v, beta);
		if (beta <= alpha)
		{
			make_play.set_corrdinate(it->get_row(), it->get_column());
			return alpha;
		}
	}
	return beta;
}

int Game::max_alpha_beta (Board b, int alpha, int beta, int level, int depth)
{
	int v;
	Board temp_board(b);
	vector<corrdinate>* possible_plys = b.get_possible_plys();
	if (level == depth)
		return SEF(temp_board);
	if (temp_board.game_finished())
	{
		if(User == 'W')
		{
			if (temp_board.get_white_score() > temp_board.get_black_score())
			{
				return (temp_board.get_white_score() - temp_board.get_black_score());
			}
			else // Draw
			{
				return 0;
			}
		}
		if(User == 'B')
		{
			if (temp_board.get_black_score() > temp_board.get_white_score())
			{
				return (temp_board.get_black_score() - temp_board.get_white_score());
			}
			else // Draw
			{
				return 0;
			}
		}
	}

	for (std::vector<corrdinate>::iterator it = possible_plys->begin(); it != possible_plys->end(); it++)
	{
		temp_board.make_ply(*it, false);
		v = min_alpha_beta (temp_board, alpha, beta, level+1, depth);
		// reset board
		beta = minimum(v, beta);
		if (alpha >= beta)
		{
			return beta;
		}
	}
	return alpha;
}

// calculate how many chips are flipped for a possible ply
int Game::SEF(Board b)
{
	int black_total, white_total, chip_diff_ratio;
	int black_score = 0, white_score = 0;
	b.get_scores();

	black_total = b.get_black_score();
	white_total = b.get_white_score();

	for(int i = 0; i < ROW; i++)
	{
		for(int j = 0; j < COLUMN; j++)
		{
			if (b.is_white(b.get_chip(i, j)))
				white_score += STATIC_GAME_BOARD_EVAL[i][j];
			else if (b.is_black(b.get_chip(i, j)))
				black_score += STATIC_GAME_BOARD_EVAL[i][j];
		}
	}

	if(player)
	{
		chip_diff_ratio = ((white_total - black_total) / (white_total + black_total)) * 100;
		return chip_diff_ratio + black_total + black_score;
	}
	else
	{
		chip_diff_ratio = ((black_total - white_total) / (white_total + black_total)) * 100;
		return chip_diff_ratio + white_total + white_score;
	}
}

int Game::minimum(int v, int b)
{
	if (v < b)
		return v;
	else
		return b;
}