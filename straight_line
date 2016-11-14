#include<iostream>
using namespace std;
struct Point{
	double x,y; //declare PointX and PointY as double
	Point(double _x = 0.0, double _y = 0.0): x(_x), y(_y){ }; //Default constructor + constructor with parameters
	Point(const Point &_copy): x(_copy.x), y(_copy.y){ }; //Copy constructor
	Point& operator=(const Point& other){
		if(this !=& other){
			x = other.x;
			y = other.y;
		}
		return *this;
	} //operator= for Point struct
};
class Line {
private:
	Point first;
	Point second;
public:
	Line(Point _first = Point(0, 0), Point _second = Point(0, 0)): first(_first), second(_second) { };
	Line(const Line& other): first(other.first), second(other.second){ };
	Line& operator=(const Line& other) {
		if (this != &other) {
			first = other.first;
			second = other.second;
		}
		return *this;
	}
	double get_FirstX() const {
		return first.x;
	}
	double get_FirstY() const {
		return first.y;
	}
	double get_SecondX() const {
		return second.x;
	}
	double get_SecondY() const {
		return second.y;
	}
	void operator<<(const ostream& out){
		//TODO
	}
};
/*
void operator<<(const ostream& out, const Line& other) {
	cout << "y= " << (other.getPTY() - other.getPOY()) / (other.getPTX() - other.getPOX()) << "*X ";
	if (-other.getPOX()*(other.getPTY() - other.getPOY()) / (other.getPTX() - other.getPOX()) + other.getPOY() > 0)
		cout << "+ ";
	cout<< -other.getPOX()*(other.getPTY() - other.getPOY()) / (other.getPTX() - other.getPOX()) + other.getPOY() << endl;
	}
	*/
int main() {
	return 0;
}
