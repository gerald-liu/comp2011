#include <iostream>
#include <cstring>
#include "puzzle.h"
using namespace std;

// Default constructor
WordPuzzle::WordPuzzle() {
   board = nullptr;
   size = 0;
}

// TODO 2: Implement the constructor to initialize a puzzle board of size n
WordPuzzle::WordPuzzle(int n) {
	board = new char*[n];
	for (int i = 0; i < n; i++) board[i] = new char[i + 1];
	for (int i = 0; i < n; i++) for (int j = 0; j <= i; j++) board[i][j] = '_';
	size = n;
}

// TODO 4:  Implement the destructor to deallocate the dyanmic puzzle
WordPuzzle::~WordPuzzle() {
	for (int i = 0; i < size; i++) delete[] board[i];
	delete[] board;
}

// Print the current state of the puzzle board
void WordPuzzle::print() {
   for (int i=0; i<size; i++) {
      for (int j=0; j<=i; j++) {
         cout << board[i][j];
         if (j!=i)
           cout << ",";
      }
      cout << endl;
   }
}

// TODO 3: Add a new word to the puzzle board at a specific position
bool WordPuzzle::add_word(const char* word, Position pos, Direction d) {
	switch (d) {
	case HORIZONTAL: 
		if (pos.col + static_cast<int>(strlen(word)) > pos.row + 1) return false;
		for (int i = 0; i < static_cast<int>(strlen(word)); i++) if (board[pos.row][pos.col + i] != '_' && board[pos.row][pos.col + i] != word[i]) return false;
		for (int i = 0; i < static_cast<int>(strlen(word)); i++) board[pos.row][pos.col + i] = word[i]; break;
	case VERTICAL: 
		if (pos.row + static_cast<int>(strlen(word)) > size) return false;
		for (int i = 0; i < static_cast<int>(strlen(word)); i++) if (board[pos.row + i][pos.col] != '_' && board[pos.row][pos.col + i] != word[i]) return false;
		for (int i = 0; i < static_cast<int>(strlen(word)); i++) board[pos.row + i][pos.col] = word[i]; break;
	case DIAGONAL: 
		if (pos.row + static_cast<int>(strlen(word)) > size) return false;
		for (int i = 0; i < static_cast<int>(strlen(word)); i++) if (board[pos.row + i][pos.col + i] != '_' && board[pos.row][pos.col + i] != word[i]) return false;
		for (int i = 0; i < static_cast<int>(strlen(word)); i++) board[pos.row + i][pos.col + i] = word[i]; break;
	}
	return true;
}

// Complete the empty positions of the puzzle board with random characters
void WordPuzzle::complete_puzzle() {
   for (int i=0; i<size; i++) {
      for (int j=0; j<=i; j++) {
         if (board[i][j] == '_')
            board[i][j] = 'a' + rand()%26;
      }
   }
}
