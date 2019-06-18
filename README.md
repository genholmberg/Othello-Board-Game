# Simple Othello AI Board Game

This project is an AI which uses an Alpha-Beta Minimax with a static evaluation function which evaluates an Othello board by stability, score, and disc parity. The AI can beat a novice human player or other AIs programs that are set to a difficulties between easy and intermediate.

An important note with Alpha-Beta Minimax function  is it predominantly dependent on the SEF for its quality. The SEF for this program is static between games and rounds. An author will be able to change the weights and values by hand to fine tune the AI game play quality.

To play against the AI, compile the Othello file (g++ Othello.cpp) and run the executable. Four options will be displayed; zero to exit, one to start a new game, two for help instructions and three for a pre-configured board to be loaded in from a text file. Select one to start a new game. Next select to use black or white discs by entering 1 or 2. Once the disc color has been chosen, the Othello board will be displayed along with axes labels; 1-8 for the rows and A-H for the columns. The user will be prompted to enter a move by entering the coordinates of the ply using the axes labels. Once the user has selected a ply, the AI will make its move and redisplay the updated board. The user should continue entering ply coordinates until the board is full of discs and a winner is determined.

This project was created for an AI class at St. Cloud State University in collaborations with Ben Jacobs.