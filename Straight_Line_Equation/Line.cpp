#include "Line.h"

Line::Line(Point _first, Point _second) : first(_first), second(_second) { };
Line::Line(const Line& other) : first(other.first), second(other.second){ };
Line& Line::operator=(const Line& other) {
	if (this != &other) {
		first = other.first;
		second = other.second;
	}
	return *this;
}
double Line::get_FirstX() const {
	return first.x;
}
double Line::get_FirstY() const {
	return first.y;
}
double Line::get_SecondX() const {
	return second.x;
}
double Line::get_SecondY() const {
	return second.y;
}
void operator<<(const std::ostream& out, const Line& other){
	std::cout << "y= " << (other.get_SecondY() - other.get_FirstY()) / (other.get_SecondX() - other.get_FirstX()) << "*X";
	if (-other.get_FirstX()*(other.get_SecondY() - other.get_FirstY()) / (other.get_SecondX() - other.get_FirstX()) + other.get_FirstY() > 0)
	{
		std::cout << " + ";
		std::cout << -other.get_FirstX()*(other.get_SecondY() - other.get_FirstY()) / (other.get_SecondX() - other.get_FirstX()) + other.get_FirstY() << std::endl;
	}
}