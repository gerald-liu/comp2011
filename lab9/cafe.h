#ifndef CAFE_H_
#define CAFE_H_

// TODO 6: Include appropriate header
#include "point.h"
#include "user.h"

// TODO 4: Add and define all the appropriate global variables here
const int MAX_NAME_LENGTH = 10;
const int MAX_CAFE_NUM = 10;
const int MAX_RATINGS_NUM = 10;

// TODO 1: Add the necessary Cafe struct here
struct Rating{
	User* userPtr;
	float rating;
};

struct Cafe {
	char name[MAX_NAME_LENGTH];
	Point location;
	Rating ratings[MAX_RATINGS_NUM];	//use the struct Rating instead of float
	int numOfRatings;
};

// TODO 5: Add the appropriate function declarations here.
float calcAvgRating(const Cafe*);  // given
void loadCafe(Cafe[], int*, string);  // given
void loadRating(Cafe cafes[], int cafeNum, User users[], int numUsers, string filename);  // given
void addCafe(Cafe cafes[], int* cafeNum, const char cafeName[], const Point* location);
void addRating(Cafe *c, User *user, float rating);
void printCafe(const Cafe* c);
void printCafeRatingByUser(const Cafe* c);
void recommendBestOptions(const Cafe cafes[], const Point* myLocation, int cafeNum);
#endif /* CAFE_H_ */
