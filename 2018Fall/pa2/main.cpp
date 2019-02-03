//  main.cpp
//	minesweeper
#include <iostream>
#include "definition.h"
using namespace std;

int main() {

	/* Initialization */
	int height, width; // board size: height * width;
	int num_mines; // total number of mines
	int num_flowers; // total number of flowers
	bool debug; // True: debug mode; False: play mode;
	int life = 1;
	int num_marked_mines = 0; 
	int win_or_lose; // 0: continue game; -1: lose; 1: win

	/* choose game level */
	int level;
	cout << "-.-.-.- Mine Sweeper -.-.-.-" << endl << endl;
	cout << "* Choose a level to start: " << endl;
	cout << " 1. Beginner: \t9 * 9 board, 10 mines, 2 flowers " << endl;
	cout << " 2. Intermediate: \t16 * 16 board, 40 mines, 5 flowers " << endl;
	cout << " 3. Advanced: \t16 * 30 board, 99 mines, 10 flowers " << endl;
	cout << "Type 1 for Beginner, 2 for Intermediate, 3 for Advanced: ";
	
	cin >> level; // assume the input is valid

	/* choose mode: play mode | debug mode */
	cout << "\n* Choose mode: " << endl;
	cout << "0. Play " << endl;
	cout << "1. Debug " << endl;
	cout << "Type 0 for Play mode, 1 for Debug mode: ";
	cin >> debug; // assume the input is valid

	cout << "\nGAME START !!!  ATTENTION: Find flowers to have additional lives !!!" << endl;

	/* initialize play board */
	switch(level) {
		case 1: height = 9; width = 9; num_mines = 10; num_flowers = 2; break;
		case 2: height = 16; width = 16; num_mines = 40; num_flowers = 5; break;
		case 3: height = 16; width = 30; num_mines = 99; num_flowers = 10; break;
		default: break;
	}

	Cell cell[MAXSIZE][MAXSIZE];
	initCell(cell);
	
	/* randomly place mines and flowers */
	generateMineAndFlower(cell, num_mines, num_flowers, height, width);

	/* generate mine count map */
	generateMinecountMap(cell, height, width);


	/* GAME START */
	int row, col, op;
	
	/* game loop*/
	while((win_or_lose = checkWin(cell,num_mines,height,width,life)) == 0){

		if(debug)
			debugMap(cell,height,width,life);

		printMap(cell,height,width,life,num_marked_mines, num_mines);
		
		cout << "What operation you want to choose: " << endl;
		cout << "op (0: sweep\t1: marked as mine\t2: unmark a cell): ";
		cin >> op;
		cout << "which cell in the map: row col?" << endl;
		cin >> row >> col;
		/* You will use recursiveSweep() in this function.
		 * op = 0, sweep a cell; op = 1, mark a cell; op = 2, unmark a cell */
		operation(cell, height, width, row, col, life, num_mines, num_marked_mines, op);
	}


	debugMap(cell,height,width,life);

	if (win_or_lose == 1)
		cout << "Congratulations!! You WIN !!" << endl;
	if (win_or_lose == -1)
		cout << "Ooooops! You FAILED!" << endl;

	return 0;
}
