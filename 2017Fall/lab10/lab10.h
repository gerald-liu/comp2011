#include <iostream>
#include "frame.h"

Frame *createFrameLinkedList(char imageData[][ROWS][COLS], int numOfFrames);

void setNumOfVehicles(Frame *head);

void removeFramesWithNoVehicles(Frame *&head);

void printFrameLinkedList(const Frame *head);