//  definition.h
//	minesweeper


#include <iostream>
#include <ctime>
using namespace std;


// Representations:
// mine: '#'
// flower: '*'
// marked as mine: 'P'
// uknown: 'X'
// empty: ' ' or '[1-8]'


/* DO NOT MODIFY */

#define MAXSIZE 50

enum Content {MINE, FLOWER, EMPTY}; // #-mine,  *-flower

/* DO NOT MODIFY */
struct Cell {
	Content content;
	bool swept; // whether it is swept. true: swept; false: not yet swept
	bool marked; // whether it is marked as a mine. true: marked; false: unmarked
	int count; // number of mines surrounding this cell. [0-9]
};

/* List of functions which need to complete. 
 * DO NOT MODIFY.
 * Please find and complete the body of each function in "submit.cpp" .
 */
void generateMineAndFlower(Cell cell[MAXSIZE][MAXSIZE], int num_mines, int num_flowers, int height, int width);
void generateMinecountMap(Cell cell[MAXSIZE][MAXSIZE], int height, int width);
int recursiveSweep(Cell cell[MAXSIZE][MAXSIZE], int height, int width, int row, int col);
void operation(Cell cell[MAXSIZE][MAXSIZE], int height, int width, int row , int col, int &life, int num_mines, int &num_markeded_mines, int op);
int checkWin(const Cell cell[MAXSIZE][MAXSIZE], int num_mines, int height, int width, int life);

/* helper functions for you to use.
 * You DO NOT need use all of them.
 * But, DO NOT MODIFY */
void debugMap(const Cell cell[MAXSIZE][MAXSIZE], int height, int width, int life);
void printMap(const Cell cell[MAXSIZE][MAXSIZE], int height, int width, int life, int num_markeded_mines, int num_mines);
bool isEmpty(const Cell cell[MAXSIZE][MAXSIZE], int row, int col);
bool isOnBoard(int row, int col, int height, int width);
int max(int x, int y);
int min(int x, int y);
void initCell(Cell[MAXSIZE][MAXSIZE]);

