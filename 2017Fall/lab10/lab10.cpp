#include "lab10.h"
#include "frame.h"

using namespace std;

// TODO 1
// Create frame linked list containing all frames and copy image from imageData to every frame.
// 
// imageData:	3D char array where images of each frame are stored
// numOfFrames:	Number of frames in total
// return:		Pointer to the head of linked list
Frame *createFrameLinkedList(char imageData[][ROWS][COLS], int numOfFrames) {
	Frame *head = nullptr, *prev = nullptr;
	for (int fi = 0; fi < numOfFrames; fi++) {
		Frame *f = new Frame;
		for (int i = 0; i < ROWS; i++) for (int j = 0; j < COLS; j++) f->image[i][j] = imageData[fi][i][j];
		f->num_vehicles = 0;
		f->next_frame = nullptr;
		if (fi == 0) head = f;
		else prev->next_frame = f;
		prev = f;
	}
	return head;
}

// TODO 2
// Set the num_vehicles field in each frame to be the number of vehicles in its image.
// 
// head:	Pointer to the head of linked list
void setNumOfVehicles(Frame *head) {
	if (head == nullptr) return;
	for (; head != nullptr; head = head->next_frame) {
		int num = 0;
		for (int i = 0; i < ROWS; i++) for (int j = 0; j < COLS; j++) if (head->image[i][j] == '*') num++;
		head->num_vehicles = num;
	}
}

// TODO 3
// Remove the frames that contain no vehicles.
// 
// head:	Pointer to the head of linked list
void removeFramesWithNoVehicles(Frame *&head) {
	if (head == nullptr) return;
	Frame *f = head, *prev = nullptr;
	for (; f != nullptr; f = prev->next_frame) {
		if (f->num_vehicles == 0) {
			if (f == head) prev = head = head->next_frame;
			else prev->next_frame = f->next_frame;
			delete f;
		}
		else prev = f;
	}
}

// Given function
// 
// Prints out the frame linked list, specified by head.
// 
// head:	Pointer to the head of linked list to be printed
// 
void printFrameLinkedList(const Frame *head) {
	for (const Frame *curr = head; curr != nullptr; curr = curr->next_frame) {
		cout << "Number of vehicles: " << curr->num_vehicles << endl;

		for (int r = 0; r < ROWS; ++r) {
			for (int c = 0; c < COLS; ++c) {
				cout << curr->image[r][c];
			}
			cout << endl;
		}
	}
	cout << endl;
}
