//helper.cpp
//minesweeper

#include "definition.h"
#include <iostream>
using namespace std;

/* ============== Helper Functions ============== */

/* prints cell contains mine '#' or flower '*',
 * and all empty cells with ' ' and surrounding
 * mine count [1, 8]
 */
void debugMap(const Cell cell[MAXSIZE][MAXSIZE], int height, int width, int life) {

	/* cheat board for debug mode */
	cout << "\nreal mine map : " << endl;

	cout << "\t";
	for (int col = 0; col < width; col ++) {
		if (col > 9)
			cout << " " << col << " ";
		else
			cout << "  " << col << " ";
	}
	cout << endl;

	for (int row = 0; row < height; row ++) {
		cout << "\t";
		for (int col = 0; col < width; col ++)
			cout << " ---";
		cout << " " << endl;

		cout << row << "\t";
		for (int col = 0; col < width; col ++)
			switch (cell[row][col].content){
				case MINE: cout << "| " << '#' << " "; break;
				case FLOWER: cout << "| " << '*' << " "; break;
				case EMPTY: {
					if (cell[row][col].count > 0)
						cout << "| " << cell[row][col].count << " ";
					else
						cout << "| " << " " << " ";
					break;
				}
				default: break;
			}
		cout << "|" << endl;
	}

	cout << "\t";
	for (int col = 0; col < width; col ++)
		cout << " ---";
	cout << " " << endl;
}

/* prints unknown cell 'X', cell marked as mine 'P',
 * cell swept either empty ' ' or flower '*'
 */
void printMap(const Cell cell[MAXSIZE][MAXSIZE], int height, int width, int life, int num_markeded_mines, int num_mines) {

	cout << "\n\t ********** current state **********" << endl;
	cout << "\t life = " << life << "\tmarked = " << num_markeded_mines << "/" << num_mines << endl;

	cout << "\t";
	for (int col = 0; col < width; col ++) {
		if (col > 9)
			cout << " " << col << " ";
		else
			cout << "  " << col << " ";
	}
	cout << endl;

	for (int row = 0; row < height; row ++) {

		cout << "\t";
		for (int col = 0; col < width; col ++)
			cout << " ---";
		cout << " " << endl;

		cout << row << "\t";
		for (int col = 0; col < width; col ++) {
			if (!cell[row][col].swept && !cell[row][col].marked) {
				// unknown cell: not swept and not marked
				cout << "| " << 'X' << " ";
				continue;
			}

			if (!cell[row][col].swept && cell[row][col].marked) {
				// cell marked as mine
				cout << "| " << 'P' << " ";
				continue;
			}

			// cell swept
			switch (cell[row][col].content){
				case MINE: cout << "| " << '#' << " "; break;
				case FLOWER: cout << "| " << '*' << " "; break;
				case EMPTY: {
					if (cell[row][col].count)
						cout << "| " << cell[row][col].count << " ";
					else
						cout << "| " << " " << " ";
					break;
				}
				default: cout << "print error!" ; break;
			}
		}
		cout << "|" << endl;
	}
	cout << "\t";
	for (int col = 0; col < width; col ++)
		cout << " ---";
	cout << " " << endl;
}

// whether a cell is an empty cell
bool isEmpty(const Cell cell[MAXSIZE][MAXSIZE], int row, int col) {
	if (cell[row][col].content == EMPTY)
		return true;
	return false;
}

// whether a coordinate is located inside the play board
bool isOnBoard(int row, int col, int height, int width) {
	if (row < 0 || row > height - 1 || col < 0 || col > width - 1)
		return false;
	return true;
}

// initialize each cell.
void initCell(Cell cell[MAXSIZE][MAXSIZE]) {
	for (int i = 0; i < MAXSIZE; i++)
		for (int j = 0; j < MAXSIZE; j++) {
			cell[i][j].content = EMPTY;
			cell[i][j].swept = false;
			cell[i][j].marked = false;
			cell[i][j].count = 0;
		}
}

int max(int x, int y) {
	return x > y ? x : y;
}

int min(int x, int y) {
	return x < y ? x : y;
}
