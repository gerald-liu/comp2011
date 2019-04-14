/* COMP2011 Spring 2019
 * Assignment 2
 * File: main.cpp
 */


#include <iostream>
#include "func.h"
using namespace std;

/* Utility function to convert the character input into the corresponding shape */
Shape handleShapeInput(char c)
{
   switch (c)
   {
      case 't':
        return TRIANGLE;
      case 'e':
        return HIVE;
      case 'v':
        return VERTICAL;
      case 'h':
        return HORIZONTAL;
      case 'u':
        return UPWARD_SLANTING_LINE;
      case 'd':
        return DOWNWARD_SLANTING_LINE;
      default:
        return NONE;
   };
}

/* Utility function to validate the input position */
void getPosition(int &row, int &col)
{
   while (true) 
   {
      cout << "Enter the row and column to start (space separated): ";
      cin >> row >> col;
      if ((row < 0) || (col < 0) || (row >= MAX_ROW) || (col >= MAX_COL))
         cout << "Invalid position!" << endl;
      else 
         break;
   } 
}

int main() 
{
   // initialize the canvas 2D array
   char canvas[MAX_ROW][MAX_COL] = {};

   cout << "//=================================\\\\" << endl;
   cout << "||  Welcome to    .----,           ||" << endl;
   cout << "||  the          /--._(            ||" << endl;
   cout << "||  painting     |____|            ||" << endl;
   cout << "||  board!       [____] .=======.  ||" << endl;
   cout << "||                 YY   q.     .p  ||" << endl;
   cout << "||  Let's start    ||   | `---' |  ||" << endl;
   cout << "||  drawing!       []   |_______|  ||" << endl;
   cout << "\\\\=================================//" << endl;
   int choice = 0;

   while (choice != 9)
   { 
      // print the menu and get the choice
      cout << endl << "=== Menu ===" << endl;
      cout << "0 - Display the board" << endl ;
      cout << "1 - Make a horizontal line" << endl ;
      cout << "2 - Make a vertical line" << endl ;
      cout << "3 - Make an upward slanting line" << endl ;
      cout << "4 - Make a downward slanting line" << endl ;
      cout << "5 - Make a hive" << endl ;
      cout << "6 - Make a triangle" << endl ;
      cout << "7 - Fill the area" << endl ;
      cout << "8 - Make a repeating pattern" << endl ;
      cout << "9 - Exit"  << endl ;
      cout << "Enter your option: ";
      cin >> choice;

      int row, col, parameter, successMove=0;
      switch (choice)
      {
         case 0: // Display the board
            printCanvas(canvas);
            break;
         case 1: // Make a horizontal line
            getPosition(row, col);
            cout << "Enter the length: ";
            cin >> parameter;
            successMove = makeHorizontalLine(canvas, row, col, parameter);
            printCanvas(canvas);
            cout << "Total number of - used: " << successMove << endl ;
            break;
         case 2: // Make a vertical line
            getPosition(row, col);
            cout << "Enter the length: ";
            cin >> parameter;
            successMove = makeVerticalLine(canvas, row, col, parameter);
            printCanvas(canvas);
            cout << "Total number of | used: " << successMove << endl ;
            break;
         case 3: // Make an upward slanting line
            getPosition(row, col);
            cout << "Enter the length: ";
            cin >> parameter;
            successMove = makeUpwardSlantingLine(canvas, row, col, parameter);
            printCanvas(canvas);
            cout << "Total number of / used: " << successMove << endl ;
            break;
         case 4: // Make a downward slanting line 
            getPosition(row, col);
            cout << "Enter the length: ";
            cin >> parameter;
            successMove = makeDownwardSlantingLine(canvas, row, col, parameter);
            printCanvas(canvas);
            cout << "Total number of \\ used: " << successMove << endl ;
            break;
         case 5: // Make a hive
            getPosition(row, col);
            cout << "Enter the depth: ";
            cin >> parameter;
            makeHive(canvas, row, col, parameter);
            printCanvas(canvas);
            break;
         case 6: // Make a triangle
            getPosition(row, col);
            cout << "Enter the layer: ";
            cin >> parameter;
            makeTriangle(canvas, row, col, parameter);
            printCanvas(canvas);
            break;
         case 7: // Fill the area
            getPosition(row, col);
            cout << "Enter the symbol: " << endl ;
            char char_parameter;
            cin >> char_parameter;
            fill(canvas, row, col, char_parameter);
            printCanvas(canvas);
            break;
         case 8: // Make a repeating pattern
            getPosition(row, col);
            int interval_row, interval_col;
            cout << "For the interval, ";
            getPosition(interval_row, interval_col);
            char shape_input;
            Shape type;
            cout << "Enter the shape to be repeated" << endl
                 << "(t - triangle, e - hive, v - vertical, h - horizontal, " << endl
                 << " u - upward slanting line, d - downward slanting line): ";
            cin >> shape_input;
            cout << "Enter the parameter value: ";
            cin >> parameter;
            int time;
            cout << "Enter the number of times it should repeat: ";
            cin >> time;
            repeatPattern(canvas, row, col, interval_row, interval_col, handleShapeInput(shape_input), parameter, time);
            printCanvas(canvas);
            break;
         case 9:
            break;
         default:
            cout << "Please insert a correct option." << endl ;
      }
   }
   return 0;
}
