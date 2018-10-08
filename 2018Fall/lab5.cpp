/*
 * Lab 5 Skeleton
 *
 */

#include <iostream>
#include <ctime>
#include <cstdlib>

using std::cout; using std::cin; using std::endl;

const int WIDTH = 10;
const int HEIGHT = 10;
const char SHIP = 'U';
const char HIT = '*';
const char EMPTY = '.';
const char MISS = 'x';

//This function is to print the map. The first parameter is a 2D array that represents the
//map. The second parameter check if it is in the debug mode.
void printMap(const char map[][WIDTH], bool debug = true) {
    cout << " ";
    for (int i = 0; i < WIDTH; i++) {
	cout << " " << i ;
    }
    cout << endl;

    for (int i = 0; i < HEIGHT; i++) {
	cout << i << " ";

	for (int j = 0; j < WIDTH; j++) {
	    if (!debug && map[i][j] == SHIP)
		cout << EMPTY << " ";
	    else
		cout << map[i][j] << " ";
	}

	cout << endl;
    }
}

// Place a ship of a particular size on the map.
// Make sure that the battle ships cannot overlap with each other, nor can
// they be placed out of the game board.
// You need to randomly place them on the board.
// You can always assume the map has enough room to place the battle ship when the function is being called.
bool canPlace(const char map[][WIDTH], int size, int row, int col, int dir) {
    while (size) {
        if (row < 0 || row >= HEIGHT || col < 0 || col >= WIDTH)
            return false;
        else if (map[row][col] != '.')
            return false;
        else if (dir == 0) row++;
        else if (dir == 1) row--;
        else if (dir == 2) col++;
        else if (dir == 3) col--;
        size--;
    }
    return true;
}

void placeShip(char map[][WIDTH], int size) {
    //add your code here
    int row, col, dir;
    do {
        row = rand() % HEIGHT;
        col = rand() % WIDTH;
        dir = rand() % 4;
    } while (!canPlace(map, size, row, col, dir));
    while (size) {
        map[row][col] = 'U';
        if (dir == 0) row++;
        else if (dir == 1) row--;
        else if (dir == 2) col++;
        else if (dir == 3) col--;
        size--;
    }
}

// To check if a cannon hits a battleship.
// Put the correct symbol on the map and return true if a ship is hit.
// Note: repeated firing on the hit area of an already damaged ship is
// considered as a miss and the symbol for the area should remain '*'.
bool isHit(char map[][WIDTH], int col, int row) {
    //add your code here
    if (map[row][col] == 'U') {
        map[row][col] = '*';
        return true;
    }
    else if (map[row][col] == '.')
        map[row][col] = 'X';
    return false;
}

// It checks if the game ends. It returns true if there is no more SHIP symbol on the map.
// It returns false otherwise.
bool isGameOver(const char map[][WIDTH]) {
    //add your code here
    for (int row = 0; row < WIDTH; row++)
        for (int col = 0; col < HEIGHT; col++)
            if (map[row][col] == 'U') return false;
    return true;
}

int main() {
    srand(time(NULL));

    char map[HEIGHT][WIDTH];
    for (int row = 0; row < HEIGHT; row++)
	for (int col = 0; col < WIDTH; col++)
	    map[row][col] = EMPTY;

    placeShip(map, 5);
    placeShip(map, 4);
    placeShip(map, 3);
    placeShip(map, 3);
    placeShip(map, 2);

    int fire_count = 0;

    char input;
    cout << "Are you playing in the debug/demo mode? (Y for yes; no Otherwise)" << endl;
    cin >> input;
    bool debug = (input == 'Y');


    while (!isGameOver(map)) {
	printMap(map, debug);

	int col, row;
	cout << "\nPlease enter your col and row separated by a space: ";
	cin >> col >> row;

	if (col < 0 || col >= WIDTH || row < 0 || row >= HEIGHT) {
	    cout << "Invalid coordinate, please enter again." << endl;
	    continue;
	}

	if (isHit(map, col, row))
	    cout << "It is a hit! " << endl << endl;
	else
	    cout << "It is a miss :( " << endl << endl;

	fire_count++;
    }

    cout << "Game over. You have fire " << fire_count
         << " cannons to destroy your enemy battleships." << endl;

    if (fire_count == 17)
	cout << "Super! You make the impossible possible!" << endl;
    else if (fire_count < 40)
	cout << "Brilliant!" << endl;
    else if (fire_count < 70)
	cout << "Good shot!" << endl;
    else
	cout << "Improve your skill next time!" << endl;

    printMap(map);
}
