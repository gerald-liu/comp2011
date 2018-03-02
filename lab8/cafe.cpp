//============================================================================
// Name        : cafe.cpp
// Author      : Serafeim Papadias
// Description : comp2017 2017S
//============================================================================

// TODO 7: Include ap#propriate header
#include "cafe.h"

float cafe::calcAvgRating() const {
	// Calculate average rating
	float sumRatings = 0.0;
	for (int i = 0 ; i < numOfRatings ; i++ )
		sumRatings += ratings[i];

	float avgRating;

	if (numOfRatings > 0)
		avgRating = sumRatings / (float)numOfRatings;
	else
		avgRating = 0;
	// Return the average
	return avgRating;
}

void cafe::printCafe() const {
	cout << "< " << name << ", Coordinates: (" << location.getX() << "," << location.getY() <<"), AVG_rating: " << calcAvgRating() << " >" << endl;
}

point cafe::getLoc() const { return location; }

char cafe::getNameIni() const { return name[0]; }

void cafe::set(const char cafeName[], const point& loc) {
	strcpy(name, cafeName);
	location = loc;
}

void cafe::addRating(float rating) {
	if (numOfRatings == MAX_RATINGS_NUM) cout << "No space to add more ratings for this cafe." << endl;
	else {
		ratings[numOfRatings] = rating;
		numOfRatings++;
	}
}

// Write the extra functions needed here
void addCafe(cafe cafes[], int& cafeNum, const char cafeName[],  const point& location) {
	if (cafeNum == MAX_CAFE_NUM) cout << "No space to add more cafes." << endl;
	else {
		cafes[cafeNum] = cafe(cafeName, location);
		cafeNum++;
	}
}

void addRating(cafe cafes[], int cafeIndex,  float rating) {
	cafes[cafeIndex].addRating(rating);
}

void recommendBasedOnRating(const cafe cafes[], int cafeNum) {
	// TODO 3: According to Part 4 in the lab description. Recommend the cafe with the highest average rating.
	int bestCafeIndex = 0;
	for (int i = 1; i < cafeNum; i++)
		if (cafes[i].calcAvgRating() > cafes[i].calcAvgRating()) bestCafeIndex = i;
	cafes[bestCafeIndex].printCafe();
}

void recommendBasedOnDistance(const cafe cafes[], const point& myLocation, int cafeNum, int N) {
	// TODO 4: According to Part 5 in the lab description. Return the N nearest cafes (no need to sort).
	cafe tempCafes[MAX_CAFE_NUM];
	for (int i = 0; i < cafeNum; i++) tempCafes[i] = cafes[i];
	sortOnDistance(tempCafes, cafeNum, myLocation);
	for (int i = 0; i < N; i++) {
		if (tempCafes[i].getNameIni() == '\0') break;
		tempCafes[i].printCafe();
	}
}

void sortOnDistance(cafe cafes[], int cafeNum, const point& loc) {
	for (int i = 1; i<cafeNum; i++) {
		cafe temp = cafes[i];
		int j = i - 1;
		while (euclideanDistance(temp.getLoc(), loc) < euclideanDistance(cafes[j].getLoc(), loc) && j >= 0) {
			cafes[j + 1] = cafes[j];    // shifts element rightwards
			j--;
		}
		cafes[j + 1] = temp;    // insert element in proper place
	}
}
