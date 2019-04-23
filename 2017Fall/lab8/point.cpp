#include "point.h"

float point::getX() const {
	return x;
}

float point::getY() const {
	return y;
}

void point::set(float forX, float forY){
	x = forX;
	y = forY;
}

float euclideanDistance(const point& p1, const point& p2)
{
	float xDiff = p1.getX() - p2.getX();
	float yDiff = p1.getY() - p2.getY();

	return sqrt(xDiff * xDiff + yDiff * yDiff);
}
