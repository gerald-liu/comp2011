//============================================================================
// Name        : lab8.cpp
// Author      : Serafeim Papadias
//				 Weiyang Liu
// Description : comp2017 2017S
//============================================================================

// TODO 7: Include appropriate header
#include "cafe.h"

int main() {

	// An array of Cafe which stores the information of all cafes.
	cafe cafes[MAX_CAFE_NUM];

	// Count the number of cafes.
	int cafeNum = 0;
	// Variables for input
	char cafeName[MAX_NAME_LENGTH];
	float x, y;
	float rating;
	int cafeIndex, N;

	cout << "*********************CAFE RECOMMENDATION*********************" << endl;
	cout << "Please input your location" << endl;
	cout << "x y" << endl;
	// Read the information of you and initialize a Consumer.
	cin  >> x >> y;

	// Store the location to a point
	point myLocation(x, y);

	// Variable for reading the choice
	int choice = 0;

	do {
		cout << "Please choose one of the following task:" << endl;
		cout << "0. Quit the program" << endl;
		cout << "1. Add a new cafe" << endl;
		cout << "2. Add a new rating" << endl;
		cout << "3. Change your location" << endl;
		cout << "4. Recommend w.r.t rating" << endl;
		cout << "5. Recommend w.r.t distance" << endl;
		// cout << "6. Recommend w.r.t {distance,rating}" << endl;
		cin >> choice;

		while (choice < 0 || choice > 5) {
			cout << "Your choice is invalid. Please input again!" << endl;
			cin  >> choice;
		}

		if (choice == 1) {
			cout << "Please input the information of the cafe." << endl;
			cout << "(name location)" << endl;
			cin  >> cafeName >> x >> y;
			// Call the addCafe
			point tempPoint(x, y);
			addCafe(cafes, cafeNum, cafeName, tempPoint);
		}

		if (choice == 2) {
			// Add a new rating
			while (true)
			{
				cout << "Please input the information of the cafe you want to rate." << endl;
				cout << "(cafeIndex rating)" << endl;
				cin  >> cafeIndex >> rating;
				if (rating >= 0 && rating <= 10)
					break;
				else
					cout << "The rating should be a number larger or equal to 0 and less than or equal to 10!" << endl;
			}
			// Call the addRating
			addRating(cafes, cafeIndex, rating);
		}

		if (choice == 3) {
			cout << "Please input your location" << endl;
			cout << "x y" << endl;
			// Read the information of you and initialize a Consumer.
			cin >> x >> y;
			// Update my location
			myLocation.set(x,y);
		}

		if (choice == 4) {
			cout << "=== Recommendation Based on Rating ===" << endl;
			recommendBasedOnRating(cafes, cafeNum);
		}

		if (choice == 5) {
			cout << "=== Recommendation Based on Distance ===" << endl;
			cout << "Set the number of nearest neighbours N  " << endl;
			cin  >> N;
			recommendBasedOnDistance(cafes, myLocation, cafeNum, N);
		}

	} while (choice != 0);

	return 0;
}
