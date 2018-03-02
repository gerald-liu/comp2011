#include <iostream>

using namespace std;


/*
 * print the game board
 *
 * this function is given and already complete
 * do NOT modify anything of it
 */
void printGameBoard(char s1, char s2, char s3, char s4, char s5, char s6, char s7, char s8, char s9)
{
	cout << "     |     |     " << endl;
	cout << "  " << s1 << "  |  " << s2 << "  |  " << s3 << endl;
	cout << "_____|_____|_____" << endl;
	cout << "     |     |     " << endl;
	cout << "  " << s4 << "  |  " << s5 << "  |  " << s6 << endl;
	cout << "_____|_____|_____" << endl;
	cout << "     |     |     " << endl;
	cout << "  " << s7 << "  |  " << s8 << "  |  " << s9 << endl;
	cout << "     |     |     " << endl << endl;
}

/*
 * print the message that asks the current player for his/her input
 *
 * you MUST call this function in your getValidInput implementation
 *
 * this function is given and already complete
 * do NOT modify anything of it
 */
void printQuestion(char currentPlayerSymbol)
{
	 cout << "Player " << currentPlayerSymbol << ", please choose an unoccupied space (0 to quit): " << endl;
}

/*
 * return 'X' (uppercase English letter X) when roundNumber is odd
 * return 'O' (uppercase English letter O) otherwise
 *
 * complete the function body code, but do NOT modify the function prototype (including the function name, parameters, and return type)
 */
char getCurrentPlayerSymbol(int roundNumber)
{
    if (roundNumber%2==1) return 'X';
    else return 'O';
}

/*
 * return whether the input is valid
 * an input is valid if and only if the input is in the valid range of [0, 9]
 * and that the input refers to an unoccupied space (i.e. not 'O' and not 'X')
 *
 * be reminded to always return either true or false in all scenarios
 *
 * complete the function body code, but do NOT modify the function prototype (including the function name, parameters, and return type)
 */

bool isInputValid(int input, char s1, char s2, char s3, char s4, char s5, char s6, char s7, char s8, char s9)
{   
    char spaces[9] = {s1, s2, s3, s4, s5, s6, s7, s8, s9};
    return (input>=0 && input<=9) && !(spaces[input-1]=='X' || spaces[input-1]=='O');
}

/*
 * use some kind of loop to retrieve a valid integer input from the player, and return it at the end of the function
 * the flow is as follows
 * 1. Print exactly the question message "Player X, please choose an unoccupied space (0 to quit): " 
 *    or "Player O, please choose an unoccupied space (0 to quit): " depending on what currentPlayerSymbol is, 
 *    using the given printQuestion function
 * 2. Retrieve the integer input using cin
 * 3. If the input is valid (use the isInputValid function), return the input; if the input is invalid, go back to step 1
 *
 * *** IMPORTANT REQUIREMENT ***
 * you must NOT use any cout statement directly to print the question message in this function - you MUST call the given printQuestion function to print the message
 *
 * you can assume the player is sane and always inputs an integer (e.g. no alphabet/symbol input etc.)
 *
 * complete the function body code, but do NOT modify the function prototype (including the function name, parameters, and return type)
 */
int getValidInput(char currentPlayerSymbol, char s1, char s2, char s3, char s4, char s5, char s6, char s7, char s8, char s9)
{  
    int input;
    do {
        printQuestion(currentPlayerSymbol);
        cin >> input;
    } while (!isInputValid(input, s1, s2, s3, s4, s5, s6, s7, s8, s9));
    return input;
}

/*
 * put the currentPlayerSymbol to one of the s1, s2, ..., s9 variables according to the input which is guaranteed to be in the range of [1, 9]
 *
 * complete the function body code, but do NOT modify the function prototype (including the function name, parameters, and return type)
 */
void putSymbol(int input, char currentPlayerSymbol, char& s1, char& s2, char& s3, char& s4, char& s5, char& s6, char& s7, char& s8, char& s9)
{
    switch (input){
        case 1: s1=currentPlayerSymbol; break;
        case 2: s2=currentPlayerSymbol; break;
        case 3: s3=currentPlayerSymbol; break;
        case 4: s4=currentPlayerSymbol; break;
        case 5: s5=currentPlayerSymbol; break;
        case 6: s6=currentPlayerSymbol; break;
        case 7: s7=currentPlayerSymbol; break;
        case 8: s8=currentPlayerSymbol; break;
        case 9: s9=currentPlayerSymbol; break;    
    }
}

/*
 * return the game state
 * game state is 1 if player 1 (X) has won the game
 * game state is 2 if player 2 (O) has won the game
 * game state is -1 if the broad is full and no one has won the game yet (i.e. draw game)
 * game state is 0 otherwise
 *
 * complete the function body code, but do NOT modify the function prototype (including the function name, parameters, and return type)
 */
int getGameState(char s1, char s2, char s3, char s4, char s5, char s6, char s7, char s8, char s9)
{  
    char spaces[9] = {s1, s2, s3, s4, s5, s6, s7, s8, s9};
    bool full = true;
    for (int i=1; i<=9; i++){
        full = full && (spaces[i-1]=='X' || spaces[i-1]=='O');
        if (!full) break;
    }
    // check rows
	for(int i=1; i<=7; i+=3){
		if(spaces[i-1]=='X' && spaces[i]=='X'  && spaces[i+1]=='X')  return 1;
		else if (spaces[i-1]=='O' && spaces[i]=='O'  && spaces[i+1]=='O') return 2;
	}
    // check columns
    for(int i=1; i<=3; i++){
		if(spaces[i-1]=='X' && spaces[i+2]=='X'  && spaces[i+5]=='X')  return 1;
		else if (spaces[i-1]=='O' && spaces[i+2]=='O'  && spaces[i+5]=='O') return 2;
    }
    // check diagonals
    if ((spaces[0]=='X' && spaces[4]=='X' && spaces[8]=='X') || (spaces[2]=='X' && spaces[4]=='X' && spaces[6]=='X')) return 1;
	else if ((spaces[0]=='O' && spaces[4]=='O' && spaces[8]=='O') || (spaces[2]=='O' && spaces[4]=='O' && spaces[6]=='O')) return 2;
    // if no one wins, then it may be a draw
    return full ? -1 : 0;
}

/*
 * return whether the game is over
 * the game is over when the game is a draw game, or either of the players has won
 *
 * complete the function body code, but do NOT modify the function prototype (including the function name, parameters, and return type)
 */
bool isGameOver(char s1, char s2, char s3, char s4, char s5, char s6, char s7, char s8, char s9)
{
    return getGameState(s1, s2, s3, s4, s5, s6, s7, s8, s9)!=0;	
}

/*
 * this is the main function
 *
 * this function is given and already complete
 * do NOT modify anything of it
 */
int main()
{
	char s1 = '1', s2 = '2', s3 = '3', s4 = '4', s5 = '5', s6 = '6', s7 = '7', s8 = '8', s9 = '9'; //variables that represent the 9 spaces in the game board
	int roundNumber = 1; //the round number, starts with 1
	int gameState = 0; //game state, refer to the getGameState function for a description

	while(!isGameOver(s1, s2, s3, s4, s5, s6, s7, s8, s9)) //keep going until the game is over
	{
		char currentPlayerSymbol = getCurrentPlayerSymbol(roundNumber); //player symbol is either 'X' or 'O', refer to the getCurrentPlayerSymbol function for a description

		//print the round number and game board
		cout << "Round " << roundNumber << ":" << endl << endl;
		printGameBoard(s1, s2, s3, s4, s5, s6, s7, s8, s9);

		//get a valid input
		int input = getValidInput(currentPlayerSymbol, s1, s2, s3, s4, s5, s6, s7, s8, s9);

		if(input == 0) //exit the program if input is 0
		{
			cout << endl << "Bye!" << endl;
			return 0;
		}
		else //put the current player symbol to the board otherwise
			putSymbol(input, currentPlayerSymbol, s1, s2, s3, s4, s5, s6, s7, s8, s9);

		//update the game state
		gameState = getGameState(s1, s2, s3, s4, s5, s6, s7, s8, s9);

		//increase the round number
		roundNumber++;

		cout << endl << endl;
	}

	//game is done at this point, show the result
	cout << "Final state:" << endl << endl;
	printGameBoard(s1, s2, s3, s4, s5, s6, s7, s8, s9);
	if(gameState == -1) cout << "Draw game! Whoops!" << endl;
	else cout << "Congratulations, player " << (gameState==1?'X':'O') << "! You won! Wow!" << endl;

	return 0;
}
