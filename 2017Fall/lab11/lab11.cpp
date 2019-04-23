#include <iostream>
#include <cstring>
#include "puzzle.h"
using namespace std;

int main()
{
   WordPuzzle *puzzle = nullptr;
   int option = 0;
   char word[20] = "";
   Position p = {0, 0};
   int dnum, s;
   Direction d;

   cout << "----- Create Your Word Puzzles -----\n";
   cout << "Enter the size of the puzzle: ";
   cin >> s;
   puzzle = new WordPuzzle(s);

   do {
      cout << "Please choose one of the followings:" << endl;
      cout << "0. Quit the program" << endl;
      cout << "1. Add a word" << endl;
      cout << "2. Print the puzzle" << endl;
      cout << "3. Complete the puzzle" << endl;

      cin >> option;
      while (option < 0 || option > 3)
      {
         cout << "Invalid option, please enter again: " << endl;
         cin >> option;
      }
      switch (option)
      {
         case 1:
            cout << "Enter a word: ";
            cin >> word;
            cout << "Enter the position (row col): ";
            cin >> p.row >> p.col;
            cout << "Enter the direction (" << HORIZONTAL << ":horizontal, "
                                           << VERTICAL << ":vertical, "
                                           << DIAGONAL << ":diagonal): ";
            cin >> dnum;
            d = static_cast<Direction>(dnum);
            while (!puzzle->add_word(word, p, d))
            {
               cout << "Invalid add! Please enter again." << endl;
               cout << "Enter a word: ";
               cin >> word;
               cout << "Enter the position (row col): ";
               cin >> p.row >> p.col;
               cout << "Enter the direction (" << HORIZONTAL << ":horizontal, "
                                           << VERTICAL << ":vertical, "
                                           << DIAGONAL << ":diagonal): ";
               cin >> dnum;
               d = static_cast<Direction>(dnum);
            }
            break;
         case 2: // TODO 1: call the member function print() of puzzle 
			 puzzle->print();
			 break;
         case 3: // TODO 1: call the member function complete_puzzle() of puzzle
			 puzzle->complete_puzzle();
			 break;
      }
   } while (option);

   delete puzzle;

   return 0;
}


