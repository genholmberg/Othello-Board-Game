/*
	Genavieve Holmberg
	Benjamin Jacobs,
*/
#include <iostream>
#include <string>
#include "Game.h"
using namespace std;

void menu(Game game);

int main()
{
	Game game;
	menu(game);
	return 0;
}

void menu(Game game)
{
	int choice;
	bool exit = false;
	while (exit == false)
	{

		cout << "---------------------------------\n"
			<< "            Othello              \n"
			<< "0. Exit\n"
			<< "1. New Game\n"
			<< "2. Help\n"
			<< "3. Debug\n";

		cin >> choice;
		switch(choice)
		{
			case 0:
				exit = true;
				break;
			case 1:
				game.play_game();
				break;
			case 2:
				cout << "a. Player 1 has the black disks and Player 2 has the white disks.\n"
					 << "b. You and your opponent take turns until the board is full of disks.\n"
					 << "c. The winner is the one with more of their color disks on the board at the end\n"
					 << "d. To flip your opponent's disk(s) to your color, you have to have a disk on\n"
					 << "   one side and place another on the other side of the disk(s).\n"
					 << "e. You can do so by placing a disk above, below,\n"
					 << "   or diagonal from the disk(s) you wish to flip.\n";
				break;
			case 3:
				game.load_board();
				game.play_game();
				break;
			default:
				cout << "Invalid input.\n";
				break;
		}
	}

}