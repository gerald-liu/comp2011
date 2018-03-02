#include "utils.h"
#include "cafe.h"

// calculate average rating of a cafe
float calcAvgRating(const Cafe* c) {
	float sumRatings = 0.0;
	for (int i = 0 ; i < c->numOfRatings ; i++ ) sumRatings += c->ratings[i].rating;
	float avgRating;
	if (c->numOfRatings > 0) avgRating = sumRatings / static_cast<float>(c->numOfRatings);
	else avgRating = 0;
	return avgRating;
}

// load cafes from a given file
void loadCafe(Cafe cafes[], int *cafeNum, string filename) {
	*cafeNum = 0;
	Point p;
	char cafeName[MAX_NAME_LENGTH];
	ifstream ifs(filename);
	while (!ifs.eof()){
		ifs >> cafeName >> p.x >> p.y;
		addCafe(cafes, cafeNum, cafeName, &p);
	}
	ifs.close();
}

// load cafe ratings from a given file
void loadRating(Cafe cafes[], int cafeNum, User users[], int numUsers, string filename) {
	ifstream ifs(filename);
	int numRating, id;
	float rating;
	for (int i = 0 ; i < cafeNum ; i++) {
		ifs >> numRating;
		for (int j = 0 ; j < numRating ; j++) {
			ifs >> id >> rating;
			User* user = searchUserById(users, numUsers, id);
			if (user != nullptr)
				addRating(&cafes[i], user, rating);
			else
				cout << "User ID: " << id << " NOT FOUND!" << endl;
		}
	}
	ifs.close();
}

// Implement the following functions
// add a Cafe object to the Cafe array, cafes.
void addCafe(Cafe cafes[], int* cafeNum, const char cafeName[],  const Point* location) {
	if (*cafeNum == MAX_CAFE_NUM) cout << "No space to add more cafes." << endl;
	else {
		strcpy(cafes[*cafeNum].name, cafeName);
		cafes[*cafeNum].location = *location;
		(*cafeNum)++;
	}
}

// Add a Rating object to the Cafe c.
void addRating(Cafe* c, User* user, float rating) {
	//TODO 2 Add Your Code Here
	if (c->numOfRatings == MAX_RATINGS_NUM) cout << "No space to add more ratings for this cafe." << endl;
	else {
		c->ratings[c->numOfRatings].userPtr = user;
		c->ratings[c->numOfRatings].rating = rating;
		c->numOfRatings++;
	}
}


// Similar to lab 8, implement this function to  show the cafe's name, location and its average rating.
void printCafe(const Cafe* c) {
	//TODO 2 Add Your Code Here
	cout << "< " << c->name << ", Coordinates: (" << c->location.x << ", " << c->location.y << "), AVG_rating: " << calcAvgRating(c) << " >" << endl;
}

// This function show the cafe ratings by each user and the average rating
void printCafeRatingByUser(const Cafe* c) {
	//TODO 2 Add Your Code Here
	cout << c->name << ", Coordinates: (" << c->location.x << ", " << c->location.y << ")" << endl;
	for (int i = 0; i < c->numOfRatings; i++) cout << c->ratings[i].userPtr->name << " Rating: " << c->ratings[i].rating << endl;
	cout << "AVG_rating: " << calcAvgRating(c) << endl;
}

// Recommend best options of cafe w.r.t rating and distance
void recommendBestOptions(const Cafe cafes[], const Point* myLocation, int cafeNum) {
	//TODO 2 Add Your Code Here
	bool notBest[MAX_CAFE_NUM] = { false };
	for (int i = 0; i < cafeNum; i++) {
		float dis1 = euclideanDistance(cafes[i].location, *myLocation);
		float rat1 = calcAvgRating(&cafes[i]);
		for (int j = i + 1; j < cafeNum; j++) {
			float dis2 = euclideanDistance(cafes[j].location, *myLocation);
			float rat2 = calcAvgRating(&cafes[j]);
			if (dis1 >= dis2 && rat1 <= rat2) notBest[i] = true;
			else if (dis1 <= dis2 && rat1 >= rat2) notBest[j] = true;
		}
	}
	for (int i = 0; i < cafeNum; i++) if (!notBest[i]) printCafe(&cafes[i]);
}



