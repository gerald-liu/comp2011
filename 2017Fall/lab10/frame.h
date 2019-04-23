#ifndef FRAME
#define FRAME

// Maximum number of frames
const int MAX_FRAMES = 16;

// Size of an image
const int ROWS = 9;
const int COLS = 30;

struct Frame
{
	// Static 2D char array containing the image for this frame
	char image[ROWS][COLS];

	// Number of vechicles in this frame. Used in TODO 2 and 3
	int num_vehicles;

	// Pointer to the next frame in linked list
	Frame* next_frame;
};

#endif