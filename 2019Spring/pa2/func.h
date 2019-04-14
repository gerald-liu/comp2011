/* COMP2011 Spring 2019 
 * Assignment 2
 * File: func.h 
 * Header file for global constants, 
 */


// Please do not change this file.
#include <iostream>

// Constants 
const int MAX_ROW = 20;
const int MAX_COL = 40;

const char NULL_CHAR = '\0';
const char HYPHEN = '-';
const char BAR = '|';
const char SLASH = '/';
const char BACKSLASH = '\\';
const char DOT = '.';
const char UNDERSCORE = '_';
const char CROSS = 'X';
const char PLUS = '+';

// User-defined enum type for represent different shapes 
enum Shape {TRIANGLE, HIVE, VERTICAL, HORIZONTAL, UPWARD_SLANTING_LINE, DOWNWARD_SLANTING_LINE, NONE};

/* Function Given */
// This function is used for printing out the Canvas
void printCanvas(char canvas[MAX_ROW][MAX_COL]);

/* TODO: Functions to be completed in pa2.cpp */
// Recursive functions for making lines
int makeHorizontalLine(char canvas[MAX_ROW][MAX_COL], int row, int col, int length);
int makeVerticalLine(char canvas[MAX_ROW][MAX_COL], int row, int col, int length);
int makeUpwardSlantingLine(char canvas[MAX_ROW][MAX_COL], int row, int col, int length);
int makeDownwardSlantingLine(char canvas[MAX_ROW][MAX_COL], int row, int col, int length);

// Recursive functions for making patterns
void makeHive(char canvas[MAX_ROW][MAX_COL], int row, int col, int depth);
void makeTriangle(char canvas[MAX_ROW][MAX_COL], int row, int col, int layer);

// Recursive function for filling an area
int fill(char canvas[MAX_ROW][MAX_COL], int row, int col, char fillChar);

// Recursive function To repeat the pattern of a kind
void repeatPattern(char canvas[MAX_ROW][MAX_COL], int row, int col, int interval_row, int interval_col, Shape choice,
        int patternParameter, int times);
