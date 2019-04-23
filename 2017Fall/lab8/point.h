#ifndef LAB8_point_H_
#define LAB8_point_H_

#include "utils.h"

class point{
private:
	float x = 0.0f;
	float y = 0.0f;

public:
	point(){}
	point(float x, float y) { set(x, y); }

	// Function prototypes
	float getX() const;
	float getY() const;

	void set(float forX, float forY);
};

float euclideanDistance(const point&, const point&);

#endif /* LAB8_point_H_ */
