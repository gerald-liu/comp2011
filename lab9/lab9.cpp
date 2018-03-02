#include "utils.h"
#include "point.h"
#include "cafe.h"
#include "user.h"

int main() {

	User users[MAXUSERNUM];
	Cafe cafes[MAX_CAFE_NUM];

	int numUsers = 0;
	int cafeNum = 0;

	cout << "LOADING USER, CAFE, RATING FROM FILE..." << endl;

	// initialize user, cafe and rating
	loadUser(users, &numUsers, "user.txt");
	loadCafe(cafes, &cafeNum, "cafe.txt");
	loadRating(cafes, cafeNum, users, numUsers, "rating.txt");

	// Variables for input
	float x, y;

	cout << "*********************CAFE RECOMMENDATION*********************" << endl;

	// Variable for reading the choice
	int choice = 0;

	do {
		cout << "\nPlease choose one of the following task:" << endl;
		cout << "0. Quit the program" << endl;
		cout << "1. Show user" << endl;
		cout << "2. Show cafe rating" << endl;
		cout << "3. Show cafe rating by user" << endl;
		cout << "4. Recommend w.r.t {distance,rating}" << endl;
		cin >> choice;

		while (choice < 0 || choice > 4) {
			cout << "Your choice is invalid. Please input again!" << endl;
			cin  >> choice;
		}
		if (choice == 1) {
			for (int i = 0 ; i < numUsers ; i++){
				printUser(&users[i]);
			}
		}

		if (choice == 2) {
			for (int i = 0 ; i < cafeNum ; i++){
				printCafe(&cafes[i]);
			}
		}

		if (choice == 3) {
			for (int i = 0 ; i < cafeNum ; i++){
				printCafeRatingByUser(&cafes[i]);
				if (i != cafeNum - 1) cout << endl;
			}
		}

		if (choice == 4) {
			cout << "=== Recommendation Based on {Rating & Distance} ===" << endl;
			cout << "Please input your location" << endl;
			cout << "x y" << endl;
			// Read the information of you and initialize a Consumer.
			cin  >> x >> y;

			// Store the location to a point
			Point myLocation = {x,y};
			recommendBestOptions(cafes, &myLocation, cafeNum);
		}

	} while (choice != 0);

	return 0;
}
