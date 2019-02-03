//  pa2.cpp
//	minesweeper

#include "definition.h"

/* ATTENTION: 
 * 1. PLEASE Read the introduction before each function carefully!
 * 2. You can ONLY add your code where you find a comment:
 *   // complete your code here
 * 3. DO NOT modify other things!!
 */

/************* Functions Requires You to Complete. *************/

/* ================================================================
 * Randomly place mines and flowers on the  play board.
 * mine and flower should not exist in the same cell.
 * ----------------------------------------------------------------
 * Input: 
 * - cell[MAXSIZE][MAXSIZE]: the play board;
 * - num_mines: number of mines;
 * - num_flowers: number of flowers;
 * - height: height of the play board, which is the number of rows;
 * - width: width of the play board, which is the number of columns;
 * ----------------------------------------------------------------
 */
bool placeObj(const Content& obj, Cell cell[MAXSIZE][MAXSIZE], bool placed[MAXSIZE][MAXSIZE], int height, int width) {
	int idx = rand() % (height * width);
	int row = idx / width;
	int col = idx % width;
	if (!placed[row][col]) {
		placed[row][col] = true;
		cell[row][col].content = obj;
		return true;
	}
	else return false;
}

void generateMineAndFlower(Cell cell[MAXSIZE][MAXSIZE], int num_mines, 
                           int num_flowers, int height, int width) {
	cout << "\nPlacing mines and flowers ......" << endl;
	// complete your code here
	srand(time(NULL));
	bool placed[MAXSIZE][MAXSIZE] = {0};
	for (int i = 0; i < num_mines; ) {
		if (placeObj(MINE, cell, placed, height, width)) i++;
		else continue;
	}
	for (int i = 0; i < num_flowers; ) {
		if (placeObj(FLOWER, cell, placed, height, width)) i++;
		else continue;
	}
}

/* ================================================================
 * Count the number of surrounding mines of all cells on the game board.
 * You should compute this number not just for empty cells, 
 * but also the mine cells and flower cells.
 * ----------------------------------------------------------------
 * Input: 
 * - cell[MAXSIZE][MAXSIZE]: the play board;
 * - height: height of the play board, which is the number of rows;
 * - width: width of the play board, which is the number of columns;
 * ----------------------------------------------------------------
 */
void generateMinecountMap(Cell cell[MAXSIZE][MAXSIZE], int height, 
	                      int width) {
	cout << "\ngenerate real maps ......" << endl;
	// complete your code here
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			cell[i][j].count = 0;
			for (int k = max(0, i-1); k < min(height, i+2); k++) {
				for (int l = max(0, j-1); l < min(width, j+2); l++)
					if (cell[k][l].content == MINE) cell[i][j].count++;
			}
		}
	}
}

/* ================================================================
 * Sweep the empty cell recursively. 
 * You are REQUIRED to implement this function using recursion. 
 * You will receive NO mark if your implementation is not an recursion.
 * ----------------------------------------------------------------
 * Input: 
 * - cell[MAXSIZE][MAXSIZE]: the play board;
 * - height: height of the play board, which is the number of rows;
 * - width: width of the play board, which is the number of columns;
 * - row: index of current row;
 * - col: index of current column;
 * Output:
 * - additional_life: how many additional lives are obtained
 * ----------------------------------------------------------------
 */
int recursiveSweep(Cell cell[MAXSIZE][MAXSIZE], int height, int width, 
	               int row, int col) {
	// complete your code here
	if (cell[row][col].marked || cell[row][col].swept) return 0;
	int add_life = 0;
	cell[row][col].swept = true;
	if (cell[row][col].content == FLOWER) {
		add_life++;
		cout << "Congratulations! You got an additional life!\n";
	}
	if (cell[row][col].count) return add_life;
	for (int k = max(0, row-1); k < min(height, row+2); k++)
		for (int l = max(0, col-1); l < min(width, col+2); l++)
			add_life += recursiveSweep(cell, height, width, k, l);
	return add_life;
}

/* ================================================================
 * Run the game according to the operation chosen
 * ATTENTION: 
 * 1. you will use recursiveSweep() in this function.
 * 2. you will use isOnBoard() to help validate the input.
 * ----------------------------------------------------------------
 * Input: 
 * - cell[MAXSIZE][MAXSIZE]: the play board;
 * - height: height of the play board, which is the number of rows;
 * - width: width of the play board, which is the number of columns;
 * - row: index of current row;
 * - col: index of current column;
 * - life: record number of lives remaining;
 * - num_mines: number of mines;
 * - num_marked_mines: number of mines marked as mine by player;
 * - op: operation taken. { 0: sweep; 1: mark; 2: unmark}
 * ----------------------------------------------------------------
 */
void checkInput(Cell cell[MAXSIZE][MAXSIZE], int& row, int& col, int height, int width, int op) {
	bool legal = false;
	while (true) {
		if (isOnBoard(row, col, height, width)) {
			if (op != 2) legal = !cell[row][col].marked && !cell[row][col].swept;
			else legal = cell[row][col].marked;
		}
		if (legal) break;
		cout << "The cell should the one which is not swept or marked.\n";
		cout << "row[0, 8]: ";
		cin >> row;
		cout << "col[0, 8]: ";
		cin >> col;
	}
}

void operation(Cell cell[MAXSIZE][MAXSIZE], int height, int width, 
	           int row , int col, int& life, int num_mines, 
	           int& num_marked_mines, int op) {
	/* choose to sweep */
	if (op == 0) {
		// complete your code here
		checkInput(cell, row, col, height, width, op);
		if (cell[row][col].marked || cell[row][col].swept) return;
		else if (cell[row][col].content == MINE) {
			cell[row][col].swept = true;
			cell[row][col].marked = true;
			life--;
			cout << "You lose one life!\n";
		}
		life += recursiveSweep(cell, height, width, row, col);
	}

	/* choose to mark */
	if (op == 1) {
	 	// complete your code here 
		checkInput(cell, row, col, height, width, op);
		if (cell[row][col].marked || cell[row][col].swept) return;
		else if (num_marked_mines < num_mines) {
			if (cell[row][col].content == FLOWER) {
				cout << "Ooooops!! This is a FLOWER!! You lose a chance to have an additional life!!\n";
				cell[row][col].swept = true;
			}
			else {
				cell[row][col].marked = true;
				num_marked_mines++;
			}
		}
	}

	/* choose to unmark */
	if (op == 2) {
		// complete your code here
		checkInput(cell, row, col, height, width, op);
		if (!cell[row][col].marked) return;
		cell[row][col].marked = false;
		num_marked_mines--;
	}
}

/* ================================================================
 * Check game state: win/lose/continue
 * ----------------------------------------------------------------
 * Input: 
 * - cell[MAXSIZE][MAXSIZE]: the play board;
 * - num_mines: number of mines;
 * - height: height of the play board, which is the number of rows;
 * - width: width of the play board, which is the number of columns;
 * - life: record number of lives remaining;
 * Output:
 * - {return -1: lose; return 0: continue; return 1: win} 
 * ----------------------------------------------------------------
 */
int checkWin(const Cell cell[MAXSIZE][MAXSIZE], int num_mines, 
             int height, int width, int life) {
	// complete your code here
	if (life <= 0) return -1;
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			if (cell[i][j].content == MINE && !cell[i][j].marked && !cell[i][j].swept) return 0;
	return 1;
}
