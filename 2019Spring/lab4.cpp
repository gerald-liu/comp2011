/* lab4    Super Tic-Tac-Toe
 * (skeleton)
 */


#include <iostream>
#include <string>
using namespace std;


/*  Check whether there's a a horizontal, vertical, or diagonal row marked
 *  Parameter: player - player id, 1 or 2
 *             board[][] - a 3x3 board
 *  Return:    true - if the player win this 3x3 board
 *             false - if not  */
bool checkWin(int player, const int board[][3]){
    // Please fill in your codes here.
    
}


/*  Check whether the board is full or not
 *  The game board is full is all its grids are marked
 *  Parameter: board[][] - a 3x3 board
 *  Return:    true - if all grids are not equal to 0
 *             false - if there exists at least one grid that's equal to 0 */
bool isBoardFull(const int board[][3]){
    
    // Please fill in your codes here.
    
}


/*  Check whether the input position x, y are valid or not
 *  Valid means 1 - x, y are within the boundary
 *              2 - this position in the game board is empty (equal to 0)
 *  Parameter: x, y - position the player want to choose
 *             lower_x, upper_x, lower_y, upper_y - the boundary that x, y cannot exceed
 *             board[][] - the whole 9x9 game board
 *  Return:    true - if x, y satisfy both requirements
 *             false - if x, y violate at least one requirement  */
bool isInputValid(int x, int y, int lower_x, int upper_x, int lower_y, int upper_y, const int board[][9]){
    
    // Please fill in your codes here.
    
}


/*  This function is used to decide which super grid player can mark given his/her opponent's move
 *  The player can only mark 1 - the super grid with bottem left and top right boundary
 *                           2 - anywhere unoccupied if the super grid has been marked
 *  Parameter:  superBoard - the 3x3 super tic tac toe
 x, y - position the opponent mark on the game board
 *              lower_x, lower_y - the bottom left boundary the player can mark
 *              upper_x, upper_y - the top right boundary the player can mark
 *  Return:     No Return but should change lower_x, lower_y, upper_x and upper_y   */
void updateBoundary(const int superBoard[][3], int x, int y, int& lower_x, int& lower_y, int& upper_x, int& upper_y){
    
    // Please fill in your codes here.
    
}


// This function is used to visualize the board,
// as ' ' denote empty, 'X' - player 1, '0' - player 2, '#' denote this part draw for both players.
void printBoard(const int board[][9], int boardsize){
    // symbol used in the game
    // ' ' - empty grid, 'X' - player 1, '0' - player 2, '#' - draw
    const char symbol[4] = {' ', 'X', 'O','#'};
    
    int i, j;
    cout<< "   0  1  2   3  4  5   6  7  8" << endl;
    cout << " |---------|---------|---------|" << endl;
    for(i = 0; i < boardsize; i++){
        cout << i << "|";
        for(j = 0; j < boardsize; j++){
            cout << " " << symbol[board[i][j]] << " ";
            if ((j + 1)%3 == 0) cout << "|";
        }
        cout << endl;
        if ((i + 1)%3 == 0) cout << " |---------|---------|---------|" << endl;
    }
}


int main(){
    
    // initialization
    // game board
    // 0 empty grid, 1(2) occupied by player1(2), 3 draw
    int board[9][9] = {};
    int superBoard[3][3] = {};
    int tempBoard[3][3] = {};
    //id of the player, 1 or 2, denotes it's who's turn
    int player;
    // game board boundary
    int lower_x = 0, upper_x = 8, lower_y = 0, upper_y = 8;
    // position to mark
    int x, y;
    // loop iterator
    int i, j;
    
    
    // Game Start!
    
    cout << "======================" << endl;
    cout << "  Super Tic-Tac-Toe!" << endl;
    cout << "======================" << endl;
    printBoard(board, 9);
    
    // player 1 start first
    player = 1;
    
    // Game loop
    do{
        cout << "Player " << player << "'s move: (" << ((player == 1)?'X':'O') << ")" << endl;
        cout << "Please give the grid position(row column):     (range [" << lower_x << ","
        << upper_x << "] [" << lower_y << "," << upper_y << "])" << endl;
        
        cin >> x >> y;
        while(!isInputValid(x, y, lower_x, upper_x, lower_y, upper_y, board)){
            cout << "Input not valid, please enter again:   (range [" << lower_x << ","
            << upper_x << "] [" << lower_y << "," << upper_y << "])" << endl;
            cin >> x >> y;
        }
        
        // Mark this grid.
        board[x][y] = player;
        
        // Copy the enclosing super grid to temp board
        for(i = 0; i < 3; i++){
            for (j = 0; j < 3; j++){
                tempBoard[i][j] = board[x/3*3 + i][y/3*3 + j];
            }
        }
        
        // After each move, check whether there is a row in this super grid.
        if (checkWin(player,tempBoard)){
            // mark all 3 x 3 grids in a super grid
            for(i = (x/3*3);i < x/3*3 + 3;i++)
                for(j = y/3*3;j < y/3*3 + 3;j++)
                    board[i][j] = player;
            // mark the super grid as this players'
            superBoard[x/3][y/3] = player;
            cout << "Player " << player << " has dominated this region!" << endl;
            
            // Check whether this player wins super tic-tac-toe
            if (checkWin(player,superBoard)){
                cout << "Player " << player << " win the game!!!" << endl;
                printBoard(board, 9);
                system("pause");
                return 0;
            }
            // Check whether draw in the whole super tic-tac-toe board
            // (If the overall 3x3 super board is full, but no one wins, it's a draw)
            if (isBoardFull(superBoard)){
                cout << "Draw!" << endl;
                printBoard(board, 9);
                system("pause");
                return 0;
            }
        }
        else{
            // check whether draw in a single super grid
            // (If this 3x3 super grid is full, but no one wins it, it's a draw)
            if (isBoardFull(tempBoard)){
                for(i = (x/3*3);i < x/3*3 + 3;i++)
                    for(j = y/3*3;j < y/3*3 + 3;j++)
                        board[i][j] = 3;
                superBoard[x/3][y/3] = 3;
                // Check whether draw in the whole super tic-tac-toe board
                if (isBoardFull(superBoard)){
                    cout << "Draw!" << endl;
                    printBoard(board, 9);
                    system("pause");
                    return 0;
                }
            }
        }
        
        // Update the boundary for next player
        updateBoundary(superBoard, x, y, lower_x, lower_y, upper_x, upper_y);
        
        printBoard(board, 9);
        
        // player switch between 1 & 2
        player = player % 2 + 1;
        
    }while(true);
    
    system("pause");
    return 0;
}
