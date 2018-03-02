/*
 * lab6.cpp
 *
 * Created on: Oct 13, 2017
 *     Author: Weiyang Liu
 */

#include <iostream>
using namespace std;

const int BOARD_SIZE = 9;

bool isValid(int arr[]){
    // insertion sort
    for (int i=1; i<9; i++){
        int temp = arr[i];
        int j = i-1;
        while (temp<arr[j] && j>=0){
            arr[j+1]=arr[j];    // shifts element rightwards
            j--;
        }
        arr[j+1]=temp;    // insert element in proper place
    }

    for (int i=0; i<9; i++){
        if (arr[i] != i+1) return false;
    }
    return true;
}

bool checkSolution(int board[][BOARD_SIZE]){
    int row[9], col[9], sqr[9];
    for (int i=0; i<9; i++){
        for (int j=0; j<9; j++){
            row[j] = board[i][j];
            col[j] = board[j][i];
            sqr[j] = board[i/3*3+j/3][i%3*3+j%3];
        }
        if (!(isValid(row) && isValid(col) && isValid(sqr))) return false;
    }
    return true;
}

bool noDup(int arr[], int val){
    for (int i=0; i<9; i++){
        if (arr[i]==val) return false;
    }
    return true;
}

bool checkInput(int board[][BOARD_SIZE], int i, int j, int val){
    int row[9], col[9], sqr[9];
    for (int k=0; k<9; k++){
        row[k] = board[i][k];
        col[k] = board[k][j];
        sqr[k] = board[i/3*3+k/3][j/3*3+k%3];
    }
    return (noDup(row, val) && noDup(col, val) && noDup(sqr, val));
}

bool solve(int board[][BOARD_SIZE], int i, int j){
    if (j == 9) {
        j = 0;
        if (++i == 9) return true;
    }
    if (board[i][j] != 0) return solve(board, i, j+1); // skip filled board
    for (int val=1; val<=9; val++) {
        if (checkInput(board, i, j, val)) {
            board[i][j] = val;
            if (solve(board, i, j+1)) return true;
        }
    }
    board[i][j] = 0; // reset on backtrack
    return false;
}

bool solveSudoku(int board[][BOARD_SIZE]){
    return solve(board, 0, 0);
}


//fill the int array given a digits string describing the puzzle board
void fillBoard(int board[][BOARD_SIZE], const char s[]){
    int len = BOARD_SIZE * BOARD_SIZE;
    for(int i = 0; i < len; ++i)
        board[i / BOARD_SIZE][i % BOARD_SIZE] = (int)(s[i] - '0');
}
void printBoard(int board[][BOARD_SIZE]){
    cout << "Sudoku board" << endl;
    for(int i = 0; i < BOARD_SIZE; ++i){
        for(int j = 0; j < BOARD_SIZE; ++j)
            cout << (j ? " " : "") << board[i][j];
        cout << endl;            
    }
}
void task1(){
    const int numOfCases = 10;
    const char sampleBoards[numOfCases][BOARD_SIZE * BOARD_SIZE + 1] = {
                                                 "143628579572139468986754231391542786468917352725863914237481695619275843854396127",
                                                 "123456789578139624496872153952381467641297835387564291719623548864915372235748916",
                                                 "123456789965718423847329165632871954589634217714295638298567341351942876476183592",
                                                 "123456789549873261867129435615798324432615978978342516296587143784931652351264897",
                                                 "123456789549178263786239415698721534235964871417583926364892157972615348851347692",
                                                 "534678912672196348197342567859761423426853791713924856961537284287419635345286179",
                                                 "323456789965718423847329165632871954589634217714295638298567351351942876476183592",
                                                 "123456789457918362689372545932164857768529431214783926895237614276848593341695278",
                                                 "723456789867912345459738612534187926782694153691325874915273468276849531348561297",
                                                 "123456789698317254457829136386741592579632418641598673964173825735284961812965347"};
    
    cout << "Please enter the ID of test cases, input -1 to run all of cases" << endl;
    int caseID;
    cin >> caseID;

    int board[BOARD_SIZE][BOARD_SIZE];//array holder for sudoku

    if(caseID == -1){ //run all test cases if entering -1
        for(caseID = 0; caseID < numOfCases; ++caseID){
            cout << "Running test case " << caseID << " ......" << endl;
            fillBoard(board, sampleBoards[caseID]);      
            printBoard(board);      
            if(checkSolution(board))
                cout << "Valid" << endl;
            else
                cout << "Invalid" << endl;
            cout << endl;
        }
    }else if(caseID >= 0 && caseID < numOfCases){
        cout << "Running test case " << caseID << " ......" << endl;
        fillBoard(board, sampleBoards[caseID]);
        printBoard(board);
        if(checkSolution(board))
            cout << "Valid" << endl;
        else
            cout << "Invalid" << endl;
        cout << endl;
    }else
        cout << "Invalid test case ID." << endl;

}

void task2(){
    const int numOfCases = 16;
    const char sampleBoards[numOfCases][BOARD_SIZE * BOARD_SIZE + 1] = {
                                                 "530070000600195000098000060800060003400803001700020006060000280000419005000080079",
                                                 "009748000700000000020109000007000240064010590098000300000803020000000006000275900",
                                                 "001700509573024106800501002700295018009400305652800007465080071000159004908007053",
                                                 "625038970009200005040095302987020030150067009000019587498601053000083640016002090",
                                                 "056090800910805702030607590000002106460951287127008000089126473001009000670040910",
                                                 "260501300700820561305006008401369800053470100800000643174600900900157284002004006",
                                                 "239000405000950007607314209071006502063085074004091600002500840385140926100820000",
                                                 "356970081000600034802501700508420106100060450604150800001897045485006072003040600",
                                                 "062403817010006003038710002040960270087030500106074089800201700050007904274650130",
                                                 "062403817010006003038710002040960270087030500106074089800201700050007904274650130",
                                                 "530070000600196000098000060800060003400803001700020006060000280000419005000080079",
                                                 "923001074100098002700430190304005621097806503060304000475203010610089430000007065",
                                                 "160000079307918256005460000014080023600043005073602901700300814081020307406871000",
                                                 "806503497504280600090400200081760005005090780067035140700901500059300802402650970",
                                                 "030652090592870061070000520000090200814200009920134786000046005149085002056700948",
                                                 "823579000059401720700620500076102008200008007130790452080000200007214835540037010"};

    cout << "Please enter the ID of test cases, input -1 to run all of cases" << endl;
    int caseID;
    cin >> caseID;

    int board[BOARD_SIZE][BOARD_SIZE];//array holder for sudoku

    if(caseID == -1){ //run all test cases if entering -1
        for(caseID = 0; caseID < numOfCases; ++caseID){
            cout << "Running test case " << caseID << " ......" << endl;
            fillBoard(board, sampleBoards[caseID]);
            printBoard(board);
            if(solveSudoku (board)){
                cout << "Solution found!" << endl;
                printBoard(board);
            }
            else
                cout << "No solution exists!" << endl;
            cout << endl;            
        }
    }else if(caseID >= 0 && caseID < numOfCases){
        cout << "Running test case " << caseID << " ......" << endl;
        fillBoard(board, sampleBoards[caseID]);
        printBoard(board);
        if(solveSudoku (board)){
            cout << "Solution found!" << endl;
            printBoard(board);
        }
        else{
            cout << "No solution exists!" << endl;
        }
        cout << endl;
    }else
        cout << "Invalid test case ID." << endl;                             
}
int main(int argc, char const *argv[]){
    cout << "***************************************************" << endl;
    cout << "Sudoku Cracker" << endl;
    cout << "***************************************************" << endl << endl;

    while(1){
        int taskID;

        cout << "Please select task" << endl;
        cout << "1: Sudoku Validator" << endl; //Enter 1 for task 1
        cout << "2: Sudoku Solver" << endl;    //Enter 2 for task 2
        cout << "Enter 0 to exit" << endl;     //Enter 0 to exit

        cin >> taskID;

        if(taskID == 1)
            task1();
        else if(taskID == 2)
            task2();
        else if(taskID == 0)
            break;
        else
            cout << "Invalid input! Please re-enter the task id." << endl;         
    }
    return 0;
}