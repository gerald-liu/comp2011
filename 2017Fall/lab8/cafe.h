//============================================================================
// Name        : cafe.h
// Author      : Serafeim Papadias
// Description : comp2017 2017S
//============================================================================

#ifndef LAB8_CAFE_H_
#define LAB8_CAFE_H_

// TODO 7: Include appropriate header
#include "utils.h"
#include "point.h"

// TODO 5: Definite all the appropriate global variables here
const int MAX_NAME_LENGTH = 10;
const int MAX_CAFE_NUM = 10;
const int MAX_RATINGS_NUM = 10;

// TODO 1: Create the necessary Cafe struct here
class cafe {
private:
	char name[MAX_NAME_LENGTH] = "";
	point location = {0, 0};
	float ratings[MAX_RATINGS_NUM];
	int numOfRatings = 0;

public:
	cafe(){
		for (int i = 0; i < MAX_RATINGS_NUM; i++) ratings[i] = 0.0f;
	}
	cafe(const char cafeName[], const point& loc) {
		set(cafeName, loc);
		for (int i = 0; i < MAX_RATINGS_NUM; i++) ratings[i] = 0.0f;
	}

	// TODO 6: Fill in the appropriate function declarations here.
	float calcAvgRating() const;
	void printCafe() const ;
	point getLoc() const;
	char getNameIni() const;

	void set(const char cafeName[], const point& loc);
	void addRating(float rating);
};

void addCafe(cafe cafes[], int& cafeNum, const char cafeName[], const point& location);
void addRating(cafe cafes[], int cafeIndex, float rating);
void recommendBasedOnRating(const cafe cafes[], int cafeNum);
void recommendBasedOnDistance(const cafe cafes[], const point& myLocation, int cafeNum, int N);

void sortOnDistance(cafe cafes[], int cafeNum, const point& loc);
#endif /* LAB8_CAFE_H_ */
