#pragma once

struct Point{
	double x, y; //declare PointX and PointY as double
	Point(double = 0.0, double = 0.0); //Default constructor + constructor with parameters
	Point(const Point &); //Copy constructor
	Point& operator=(const Point& other); //operator= for Point struct
};

