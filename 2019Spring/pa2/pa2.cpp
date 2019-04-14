/* COMP2011 Spring 2019
 * Assignment 2
 * File: pa2.cpp
 * Function definitions
 *
 * Student name: Gerald Liu
 * Student ID: 36258909
 * Student email: gerald-liu@johndoe.com
 * Student lab section: LA0
 */

#include <iostream>
#include "func.h"
using namespace std;

// This function is used for printing out the Canvas
void printCanvas(char canvas[MAX_ROW][MAX_COL])
{
    cout << "The current canvas: " << endl;
    cout << "   " ;
    for (int i=0; i<MAX_COL; i++)
        cout << i % 10;
    cout << endl;
    cout << " //" ;
    for (int i=0; i<MAX_COL; i++)
        cout << "=";
    cout << "\\\\" << endl;
    for (int i=0; i<MAX_ROW; i++){
        cout << i % 10 << "||";
        for (int j=0; j<MAX_COL; j++){
            if (canvas[i][j] == NULL_CHAR)
                cout << ' ';
            else
                cout << canvas[i][j];
        }
        cout << "||" << endl;
    }
    cout << " \\\\";
    for (int i=0; i<MAX_COL; i++)
        cout << "=";
    cout << "//" << endl;
}

// TODO: Please implemement the required recursive functions stated in the header file (func.h) below. 
struct Symbol {
    const char symbol;
    const char crossing;
    const char intersection;

    Symbol(char s, char c, char i): symbol{ s }, crossing { c }, intersection { i } {}
};

const Symbol S_HYPHEN = Symbol(HYPHEN, BAR, PLUS);
const Symbol S_BAR = Symbol(BAR, HYPHEN, PLUS);
const Symbol S_SLASH = Symbol(SLASH, BACKSLASH, CROSS);
const Symbol S_BACKSLASH = Symbol(BACKSLASH, SLASH, CROSS);

struct Line {
    const Shape shape;
    const Symbol symbol;
    const int row_increment;
    const int col_increment;

    Line(Shape shape, const Symbol& symbol, int ri, int ci):
        shape{ shape }, symbol{ symbol }, row_increment{ ri }, col_increment{ ci } {}
};

const Line L_HORIZONTAL = Line(Shape::HORIZONTAL, S_HYPHEN, 0, 1);
const Line L_VERTICAL = Line(Shape::VERTICAL, S_BAR, 1, 0);
const Line L_UPWARD_SLANTING = Line(Shape::UPWARD_SLANTING_LINE, S_SLASH, -1, 1);
const Line L_DOWNWARD_SLANTING = Line(Shape::DOWNWARD_SLANTING_LINE, S_BACKSLASH, 1, 1);
const Line L_HORIZONTAL_BACKWARDS = Line(Shape::HORIZONTAL, S_HYPHEN, 0, -1);

bool onCanvas(int row, int col) {
    return (row >= 0) && (row < MAX_ROW) && (col >= 0) && (col < MAX_COL);
}

char updateChar(char old_char, const Symbol& new_symbol) {
    if (old_char == new_symbol.crossing)
        return new_symbol.intersection;
    else
        return new_symbol.symbol;
}

bool updateCell(char canvas[MAX_ROW][MAX_COL], int row, int col, const Symbol& new_symbol) {
    if (!onCanvas(row, col))
        return false;
    canvas[row][col] = updateChar(canvas[row][col], new_symbol);
    return true;
}

int makeLine(char canvas[MAX_ROW][MAX_COL], int row, int col, int length, const Line& line) {
    if (length <= 0 || !updateCell(canvas, row, col, line.symbol))
        return 0;
    else
        return 1 + makeLine(canvas, row + line.row_increment, col + line.col_increment, length-1, line);
}

int makeHorizontalLine(char canvas[MAX_ROW][MAX_COL], int row, int col, int length) {
    return makeLine(canvas, row, col, length, L_HORIZONTAL);
}

int makeVerticalLine(char canvas[MAX_ROW][MAX_COL], int row, int col, int length) {
    return makeLine(canvas, row, col, length, L_VERTICAL);
}

int makeUpwardSlantingLine(char canvas[MAX_ROW][MAX_COL], int row, int col, int length) {
    return makeLine(canvas, row, col, length, L_UPWARD_SLANTING);
}

int makeDownwardSlantingLine(char canvas[MAX_ROW][MAX_COL], int row, int col, int length) {
    return makeLine(canvas, row, col, length, L_DOWNWARD_SLANTING);
}

void makeHive(char canvas[MAX_ROW][MAX_COL], int row, int col, int depth) {
    if (depth <= 0 || !onCanvas(row, col))
        return;
    canvas[row][col] = UNDERSCORE;

    if (onCanvas(row, col+1))
        canvas[row][col+1] = SLASH;
    if (onCanvas(row+1, col+1))
        canvas[row+1][col+1] = BACKSLASH;
    
    makeHive(canvas, row-1, col-2, depth-1);
    makeHive(canvas, row-1, col+2, depth-1);
    makeHive(canvas, row+1, col-2, depth-1);
    makeHive(canvas, row+1, col+2, depth-1);
}

void makeTriangle(char canvas[MAX_ROW][MAX_COL], int row, int col, int layer) {
    if (layer < 0 || !onCanvas(row, col))
        return;
    else if (layer == 0) {
        canvas[row][col] = DOT;
        return;
    }
    
    makeHorizontalLine(canvas, row, col, layer);
    if (onCanvas(row, col + layer))
        canvas[row][col + layer] = BACKSLASH;
    
    makeLine(canvas, row, col, layer, L_HORIZONTAL_BACKWARDS);
    if (onCanvas(row, col - layer))
        canvas[row][col - layer] = SLASH;

    makeTriangle(canvas, row-1, col, layer-1);
}

int fill(char canvas[MAX_ROW][MAX_COL], int row, int col, char fillChar) {
    if (!onCanvas(row, col) || canvas[row][col] != NULL_CHAR)
        return 0;
    canvas[row][col] = fillChar;

    return 1 + fill(canvas, row-1, col, fillChar) + fill(canvas, row+1, col, fillChar)
        + fill(canvas, row, col-1, fillChar) + fill(canvas, row, col+1, fillChar);
}

void repeatPattern(char canvas[MAX_ROW][MAX_COL], int row, int col,
        int interval_row, int interval_col, Shape choice, int patternParameter, int times)
{
    if (!times)
        return;
    switch (choice) {
        case Shape::TRIANGLE:
            makeTriangle(canvas, row, col, patternParameter);
            break;
        case Shape::HIVE:
            makeHive(canvas, row, col, patternParameter);
            break;
        case Shape::VERTICAL:
            makeVerticalLine(canvas, row, col, patternParameter);
            break;
        case Shape::HORIZONTAL:
            makeHorizontalLine(canvas, row, col, patternParameter);
            break;
        case Shape::UPWARD_SLANTING_LINE:
            makeUpwardSlantingLine(canvas, row, col, patternParameter);
            break;
        case Shape::DOWNWARD_SLANTING_LINE:
            makeDownwardSlantingLine(canvas, row, col, patternParameter);
            break;
    }

    repeatPattern(canvas, row - interval_row, col - interval_col,
        interval_row, interval_col, choice, patternParameter, times - 1);
    repeatPattern(canvas, row - interval_row, col + interval_col,
        interval_row, interval_col, choice, patternParameter, times - 1);
    repeatPattern(canvas, row + interval_row, col - interval_col,
        interval_row, interval_col, choice, patternParameter, times - 1);
    repeatPattern(canvas, row + interval_row, col + interval_col,
        interval_row, interval_col, choice, patternParameter, times - 1);
}