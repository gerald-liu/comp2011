/*
 * lab4.cpp
 *
 * Created on: Sep 29, 2017
 *     Author: Weiyang Liu
 */

#include <iostream>
using namespace std;

//Task 1 Write a function printMaze to print the maze.
void printMaze(char maze[], int height, int width){
    for (int i=0; i<height; i++){
        for (int j=0; j<width; j++){
            cout << maze[i*width+j];
        }
        cout << '\n';
    }
    return;
}

//Task 2 Write a function isValidMove to check if the move is valid or not.

bool isValidMove(char maze[], int height, int width, int x, int y, char move){
    switch (move) {
        case 'w':
            y--;
            break;
        case 's':
            y++;
            break;
        case 'a':
            x--;
            break;
        case 'd':
            x++;
            break;
        default:
            return false;
    }
    return x>=0 && x<width && y>=0 && y<height && maze[y*width+x]!='#';
}

//Task 3 Write a function updateMaze to update the position of the player in the maze.
void updateMaze(char maze[], int height, int width, int x, int y){
    for (int i=-1; i<=1; i+=2){
        if (maze[(y+i)*width+x]=='P'){
            maze[(y+i)*width+x]=' ';
            goto label;
        }
    }
    for (int i=-1; i<=1; i+=2){
        if (maze[y*width+x+i]=='P'){
            maze[y*width+x+i]=' ';
            goto label;
        }
    }
    label: maze[y*width+x]='P';
	return;
	
	
}

int main() {
	const int HEIGHT = 9;
	const int WIDTH = 18;
	char maze[] = {'#', '#', '#', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#',
				   '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#',
				   '#', '#', '#', '#', '#', '#', '#', '#', ' ', '#', '#', '#', ' ', '#', '#', '#', '#', '#',
				   '#', ' ', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#', '#', ' ', '#', ' ', '#',
				   ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
				   ' ', ' ', '#', ' ', '#', '#', '#', ' ', '#', ' ', '#', ' ', '#', '#', '#', '#', ' ', ' ',
				   '#', '#', '#', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', ' ', ' ', ' ', ' ', '#', ' ', '#',
				   '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#',
				   '#', '#', ' ', '#', '#', '#', '#', '#', ' ', ' ', '#', 'E', '#', '#', '#', '#', '#', '#',
	};

	int x = 1, y = 1;
	char move;
	updateMaze(maze, HEIGHT, WIDTH, x, y);
	bool isValid;
	do {
		printMaze(maze, HEIGHT, WIDTH);
		cout << "Your current position is at: (" << x << ", " << y << ")"
				<< endl;
		do {
			cout << "Please enter your move: (up:w, down:s, left:a, right:d)  ";
			cin >> move;
			isValid = isValidMove(maze, HEIGHT, WIDTH, x, y, move);
			if (isValid) {
				switch (move) {
				case 'w':
					y--;
					break;
				case 's':
					y++;
					break;
				case 'a':
					x--;
					break;
				case 'd':
					x++;
					break;
				default:
					break;
				}
				updateMaze(maze, HEIGHT, WIDTH, x, y);
			} else {
				cout << "The move is invalid!" << endl;
			}
		} while (!isValid);
	} while (!(x == 11 && y == 8));

	cout << "Amazing! You have completed the maze!" << endl;

	return 0;

}