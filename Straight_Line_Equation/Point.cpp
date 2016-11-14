#include "Point.h"
Point::Point(double _x, double _y) : x(_x), y(_y){ };
Point::Point(const Point &_copy) : x(_copy.x), y(_copy.y){ };
Point& Point::operator=(const Point& other){
	if (this != &other){
		x = other.x;
		y = other.y;
	}
	return *this;
}
