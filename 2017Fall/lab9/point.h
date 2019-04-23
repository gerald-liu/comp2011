#ifndef POINT_H_
#define POINT_H_

#include "utils.h"

struct Point{
	float x;
	float y;
};

// Function prototypes
float euclideanDistance(const Point&, const Point&);

#endif /* POINT_H_ */
