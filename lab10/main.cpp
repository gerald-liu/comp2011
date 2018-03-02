#include <iostream>
#include <fstream>
#include <string>
#include "frame.h"
#include "lab10.h"

using namespace std;

// Given function
// 
// Load video in file and construct a 3D char array containing all images.
// 
// file:		Path to the video to load
// imageData:	Returns the 3D char array containing all images
// numOfFrames:	Returns the number of frames in the file
// 
// return:		true on success reading a video file, false on failure
// 
bool loadVideo(const string &file, char imageData[][ROWS][COLS], int &numOfFrames)
{
	ifstream video_stream;
	video_stream.open(file);
	if (!video_stream.is_open())
		return false;
	cout << "Reading video file. ";

	// read first line
	string word;
	video_stream >> word >> numOfFrames;
	cout << "Totally " << numOfFrames << " frames. ";

	// read all frame
	for (int f = 0; f < numOfFrames; ++f)
	{
		int frame_id;
		video_stream >> word >> frame_id;
		for (int i = 0; i < ROWS; ++i)
		{
			for (int j = 0; j < COLS; ++j)
			{
				video_stream >> imageData[f][i][j];
			}
		}
	}
	cout << "Finished.\n\n";

	return true;
}

int main(int argc, char **argv)
{
	char imageData[MAX_FRAMES][ROWS][COLS];
	int numOfFrames = 0;
	Frame *head;

	if (!loadVideo("video.txt", imageData, numOfFrames)) {
		cout << "Cannot read video. Please check \"video.txt\"." << endl;
		return 1;
	}

	head = createFrameLinkedList(imageData, numOfFrames);

	while (true) {

		int option = 0;

		cout << "1. printFrameLinkedList()." << endl;
		cout << "2. Test setNumOfVehicles()." << endl;
		cout << "3. Test removeFramesWithNoVehicles()." << endl;
		cout << "Others. Exit." << endl << endl;

		cout << "Option: ";
		cin >> option;

		switch (option) {
			case 1:
				printFrameLinkedList(head);
			break;
			case 2:
				setNumOfVehicles(head);
				printFrameLinkedList(head);
			break;
			case 3:
				setNumOfVehicles(head);
				removeFramesWithNoVehicles(head);
				printFrameLinkedList(head);
			break;
			default:
				return 0;
			break;
		}
	}

	return 0;
}