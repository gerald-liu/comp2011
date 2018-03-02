/*
 * pa2.cpp
 *
 * Created on: Oct 15, 2017
 *     Author: Weiyang Liu
 */

#include <iostream>

using namespace std;

/**
 * You should use the following const and enum whenever necessary. Do not hard code
 * the size of game board, the char of an EMPTY spot and the char of an OCCUPIED spot.
 *
 */
const int BOARD_SIZE = 4; // we will assign BOARD_SIZE to
                          // different values (>=3) to test your program.
const char EMPTY = '.';  // symbol that represents an EMPTY spot
const char OCCUPIED = 'x'; // symbol that represents an OCCUPIED spot
enum direction {DOWN, RIGHT}; //a block is placed to right (RIGHT)  or downward (DOWN).
/**
 * Given function. To print the game board.
 * It is already completed. Do not modify it.
 */
void printBoard(const char board[BOARD_SIZE][BOARD_SIZE]) {
    cout << "* ";
    for (int j = 0; j < BOARD_SIZE; j++)
		cout << (j % 10) << " ";
    cout << "* " << endl;
    for (int i = 0; i < BOARD_SIZE; i++) {
		cout << (i % 10) << " ";
		for (int j = 0; j < BOARD_SIZE; j++)
	    	cout << board[i][j] << ' ';
		cout << "*" << endl;
    }
    for (int j = 0; j < BOARD_SIZE + 2; j++)
		cout << "* ";
    cout << endl;
}

/**
 * Given function, to initialize a game board
 * It is already completed. Do not modify it.
 */
void initBoard(char board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++)
	for (int j = 0; j < BOARD_SIZE; j++)
	    board[i][j] = EMPTY;

}

/**
 * @TODO function
 *
 * You need to return the smallest block available to use from an input array.
 * This function takes two parameters:
 * 1) blocks - an array storing the number of blocks remains for each block size. For instance, blocks[0]
 * should store how many 'Size 1' blocks are remaining and blocks[4] should store how many 'Size 5' blocks are remaining.
 * 2) size - a variable that may be useful when constructing your recursion.
 *
 * When this function is called in the main program, the variable "size" is always set as BOARD_SIZE.
 *
 * Example, assume the blocks array is {0, 1, 0, 2}; this should return 2;
 *                 the blocks array is {2, 0, 0, 1}; this should return 1;
 *                 the blocks array is {0, 0, 1, 2}; this should return 3; etc.
 *
 * Note, if the blocks array contains only 0s (all blocks are used), this should return BOARD_SIZE + 1.
 *
 */
int getSmallestNonZeroIndex(const int arr[], int lo, int hi){
	if (lo == hi) {
		if (arr[hi] == 0) return 1; // array contains only 0s, return index = BOARD_SIZE
		else return 0;
	}
	else if (arr[lo] != 0) return 0;
	else return 1 + getSmallestNonZeroIndex(arr, lo + 1, hi);
}

int getSmallestBlock(const int blocks[], int size) {
	return 1 + getSmallestNonZeroIndex(blocks, 0, size - 1); // size = index + 1
}


/**
 * @TODO function.
 *
 * This function takes the following parameters
 * 1) char board[BOARD_SIZE][BOARD_SIZE] - a game board
 * 2) int row, int col - the top-left corner of the position that you want to put a block
 * 3) direction d, the direction you want to put a block, either downward (DOWN) or towards right (RIGHT)
 * 4) the size of a block
 *
 * If there is enough empty spot to place the block, the function shall fill the locations of the board with
 * OCCUPIED (x) and it should return true to its caller.
 * If there is not enough empty spot to place the block, or some part of the block is placed out of the game
 * board, the function shall not modify the board array and return false to its caller.
 *
 * You need to complete this function with recursion.
 */


bool canPlaceBlock(const char board[BOARD_SIZE][BOARD_SIZE], int row, int col, direction d, int size){
	if (size == 1) 
		return (board[row][col] == OCCUPIED) ? false : true;
	else if (d == DOWN) {
		if (row + size > BOARD_SIZE) return false;
		else if (board[row + size - 1][col] == OCCUPIED) return false;
		else return canPlaceBlock(board, row, col, d, size-1);
	}
	else {
		if (col + size > BOARD_SIZE) return false;
		else if (board[row][col + size - 1] == OCCUPIED) return false;
		else return canPlaceBlock(board, row, col, d, size-1);
	}
}

void placeTheBlock(char board[BOARD_SIZE][BOARD_SIZE], int row, int col, direction d, int size){
	if (size == 1) {
		board[row][col] = OCCUPIED;
		return;
	}
	else if (d == DOWN){
		board[row + size - 1][col] = OCCUPIED;
		return placeTheBlock(board, row, col, d, size-1);
	}
	else {
		board[row][col + size - 1] = OCCUPIED;
		return placeTheBlock(board, row, col, d, size-1);
	}
}

bool placeBlock(char board[BOARD_SIZE][BOARD_SIZE], int row, int col, direction d, int size) {
	if (canPlaceBlock(board, row, col, d, size)) {
		placeTheBlock(board, row, col, d, size);
		return true;
	}
	else return false;
}


/**
 * @TODO function.
 *
 * You need to check if a player have any possible way to fit a block to the board.
 * This function takes the input
 * 1) board - the 2D array representing the board
 * 2) row, col - two variables that may be useful to construct your recursion
 * 3) size - the size of a block
 *
 * The function shall return true if there is NO anyway to fit a block to the board
 * and return false if there is one or more than one way to fit a block into the board.
 *
 * When this function is called from the main program, we always fill the variable row
 * and col as 0. But when you implement this function, these two parameter may be useful
 * to construct your recursion.
 *
 */

bool cannotFitThisBlock(char board[BOARD_SIZE][BOARD_SIZE], int row, int col, int size) {
	if (row == BOARD_SIZE - 1 && col == BOARD_SIZE - 1) 
		return (canPlaceBlock(board, row, col, DOWN, size) || canPlaceBlock(board, row, col, RIGHT, size)) ? false : true;
	else if (col == BOARD_SIZE - 1) 
		return (canPlaceBlock(board, row, col, DOWN, size) || canPlaceBlock(board, row, col, RIGHT, size)) ? false : cannotFitThisBlock(board, row + 1, 0, size);
	else return (canPlaceBlock(board, row, col, DOWN, size) || canPlaceBlock(board, row, col, RIGHT, size)) ? false : cannotFitThisBlock(board, row, col + 1, size);
}


/**
 * @TODO
 *
 * This function should determine if there is any "checkmate move". A checkmate move is a valid move that 
 * if a player makes that move, his opponent will lose the game immediately. If there is such case, the 
 * function should return true and assign that move to the variables row, col, direction, size. If there is no
 * "checkmate move" the function should return false and the reference variables should not be modified.
 *
 * Similar to the above functions, row and col should be representing the top-left corner of the position
 * of the block and direction should be either RIGHT or DOWN that represents towards right or downward.
 * The variable size is the size of the block and it is required there are still unused blocks of that size
 * available, that is, blocks[size - 1] > 0.
 *
 * This function requires the status of board and the remaining number of blocks and they are supplied in the
 * array board and blocks respectively. You can assume the size of these two arrays are always "correct" when
 * it is tested. That is, you don't need to worry about if board or blocks have insufficient sizes and leading
 * array out of bound.
 *
 * When this function is called in the main program or our testing code, the variables will be set as:
 * row = 0, col = 0, direction = RIGHT, size = 1
 *
 * Note, it is possible to have more than one checkmate move. In this case you are required to assign ANY ONE
 * of the checkmate moves into the variables row, col, direction, size.
 */

void undoPlaceTheBlock(char board[BOARD_SIZE][BOARD_SIZE], int row, int col, direction d, int size){
	if (size == 1){
		board[row][col] = EMPTY;
		return;
	}
	else if (d == DOWN){
		board[row + size - 1][col] = EMPTY;
		return undoPlaceTheBlock(board, row, col, d, size-1);
	}
	else {
		board[row][col + size - 1] = EMPTY;
		return undoPlaceTheBlock(board, row, col, d, size-1);
	}
}

bool noBlockToFit(char board[BOARD_SIZE][BOARD_SIZE], const int blocks[BOARD_SIZE], int size){
	if (size == 1) return (blocks[size - 1] > 0) ? cannotFitThisBlock(board, 0, 0, size) : true;
	else if (blocks[size - 1] > 0) return cannotFitThisBlock(board, 0, 0, size) ? noBlockToFit(board, blocks, size - 1) : false;
	else return noBlockToFit(board, blocks, size - 1);
}

// check whether a certain move can checkmate
int hasCheckMate(char board[BOARD_SIZE][BOARD_SIZE], int row, int col, direction d, int blocks[BOARD_SIZE], int size){
	if (size == BOARD_SIZE){
		if (blocks[size - 1] > 0){
			if (placeBlock(board, row, col, d, size)){
				blocks[size - 1]--;
				if (noBlockToFit(board, blocks, BOARD_SIZE)){
					undoPlaceTheBlock(board, row, col, d, size);
					blocks[size - 1]++;
					return size;
				}
				else {
					undoPlaceTheBlock(board, row, col, d, size);
					blocks[size - 1]++;
					return 0;
				}
			}
			else return 0;
		}
		else return 0;
	}
	else if (blocks[size - 1] > 0) {
		if (placeBlock(board, row, col, d, size)){
			blocks[size - 1]--;
			if (noBlockToFit(board, blocks, BOARD_SIZE)){
				undoPlaceTheBlock(board, row, col, d, size);
				blocks[size - 1]++;	
				return size; 
			}
			else {
				undoPlaceTheBlock(board, row, col, d, size);
				blocks[size - 1]++;
				return hasCheckMate(board, row, col, d, blocks, size + 1);
			}
		}
		else return hasCheckMate(board, row, col, d, blocks, size + 1);
	}
	else return hasCheckMate(board, row, col, d, blocks, size + 1);
}

bool checkMate(char board[BOARD_SIZE][BOARD_SIZE], int& row, int& col, direction& d, int blocks[BOARD_SIZE], int& size) {
	if (row == BOARD_SIZE - 1 && col == BOARD_SIZE - 1) {
		if (hasCheckMate(board, row, col, d, blocks, size)) {
			size = hasCheckMate(board, row, col, d, blocks, size);
			return true;
		}
		else {
			d = static_cast<direction>((d + 1) % 2);
			if (hasCheckMate(board, row, col, d, blocks, size)) {
				size = hasCheckMate(board, row, col, d, blocks, size);
				return true;
			}
			else return false;
		}
	}
	else if (col == BOARD_SIZE - 1) {
		if (hasCheckMate(board, row, col, d, blocks, size)) {
			size = hasCheckMate(board, row, col, d, blocks, size);
			return true;
		}
		else {
			d = static_cast<direction>((d + 1) % 2);
			if (hasCheckMate(board, row, col, d, blocks, size)) {
				size = hasCheckMate(board, row, col, d, blocks, size);
				return true;
			}
			else {
				row++;
				col = 0;
				return checkMate(board, row, col, d, blocks, size);
			}
		}
	}
	else{
		if (hasCheckMate(board, row, col, d, blocks, size)) {
			size = hasCheckMate(board, row, col, d, blocks, size);
			return true;
		}
		else {
			d = static_cast<direction>((d + 1) % 2);
			if (hasCheckMate(board, row, col, d, blocks, size)) {
				size = hasCheckMate(board, row, col, d, blocks, size);
				return true;
			}
			else {
				col++;
				return checkMate(board, row, col, d, blocks, size);
			}
		}
	}
}

int main() {
    char board[BOARD_SIZE][BOARD_SIZE];
    int blocks[BOARD_SIZE];
    int turn = 0; // 0 for player 1; 1 for player 2;

    //initialize game board
    initBoard(board);

    //initialize number blocks
    for (int i = 0; i < BOARD_SIZE - 1; i++) {
	blocks[i] = 2;
    }
    blocks[BOARD_SIZE - 1] = 1;


    do {
		cout << "It is your turn, player " << (turn + 1) << endl;
		printBoard(board);
		cout << "Remaining Blocks" << endl;
		for (int i = 0; i < BOARD_SIZE; i++)
		    cout << (i+1) << " ";
		cout << endl;
		for (int i = 0; i < BOARD_SIZE; i++)
		    cout << blocks[i] << " ";
		cout << endl;

		int row = 0, col = 0;
		int size = 1;
		int d = 0;

		direction dir = RIGHT;
		if (checkMate(board, row, col, dir, blocks, size)) {
		    cout << "There is check mate move: (" << row << ", " << col << "), place size " << size <<
			    ((dir == RIGHT)? " to right": " down") << endl;
		}

		while (1) {
		    cout << "Please enter the coordinate: row col" << endl;
		    cin >> row >> col;
		    if (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE)
			break;
		    cout << "Invalid input" << endl;
		}

		while (1) {
		    cout << "Please enter the size of the block: (1 to "<< BOARD_SIZE <<")" << endl;
		    cin >> size;
		    if (size > 0 && size <= BOARD_SIZE && blocks[size - 1] != 0)
			break;
		    cout << "Invalid input or block of that size are used up." << endl;
		}

		while (1) {
		    cout << "Direction? 1 for Right, 0 for Down: " << endl;
		    cin >> d;
		    if (d == 0 || d == 1)
			break;
		    cout << "Invalid input" << endl;
		}


		if (!placeBlock(board, row, col, static_cast<direction>(d) , size))
		    cout << "Cannot place the block, please try again" << endl;
		else {
		    turn = (turn + 1) % 2 ;
		    blocks[size - 1]--;
		}
		if (getSmallestBlock(blocks, BOARD_SIZE) > BOARD_SIZE) {
		    printBoard(board);
		    cout << "Game over. Block completed. " << endl;
		}

    }  while(!cannotFitThisBlock (board, 0, 0, getSmallestBlock(blocks, BOARD_SIZE)));
    printBoard(board);
    cout << "Player " << (turn + 1) << ":no more move, game over!" << endl;
    
}