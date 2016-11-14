#pragma once
#include<iostream>
#include<ostream>
#include "Point.h"

class Line {
private:
	Point first;
	Point second;
public:
	Line(Point = Point(0, 0), Point = Point(0, 0));
	Line(const Line& other);
	Line& operator=(const Line& other);
	double get_FirstX() const;
	double get_FirstY() const;
	double get_SecondX() const;
	double get_SecondY() const;
	friend void operator<<(const std::ostream&, const Line&);
};