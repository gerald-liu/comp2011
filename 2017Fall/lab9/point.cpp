#include "point.h"

float euclideanDistance(const Point& p1, const Point& p2)
{
	float xDiff = p1.x - p2.x;
	float yDiff = p1.y - p2.y;

	return sqrt(xDiff * xDiff + yDiff * yDiff);
}