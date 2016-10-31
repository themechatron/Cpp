#include<iostream>
using namespace std;
/*
class Point{
	double x, y;
public:
	Point(double _x, double _y) : x(_x), y(_y){}
	static Point getZero(){
		return Point(0, 0);
	}
	void doStuff(){
		Point zero = getZero();
		std::cout << "Stuff" << std::endl;
	}
};

class A{
	static int x[];
public:
	int y;
	int &operator[](size_t ind){ return x[ind]; }
};
int A::x[] = { 1, 2, 3 };
*/

class Singleton{
	static Singleton s;
	int a, b;
	Singleton(int x, int y):a(x),b(y){}
public:
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;
	static int getA(){
		return s.a;
	}
	static void setA(int _a){
		s.a = _a;
	}
};

Singleton Singleton::s(1, 2);
int main(){
	/*
	Point p1(2, 5);
	p1.doStuff();

	Point p2 = p1.getZero();
	Point p3 = Point::getZero();
	std::cout << sizeof(A) << std::endl;
	A a1;
	std::cout << a1[0] << std::endl;
	*/

	//Singleton
	std::cout << Singleton::getA() << " " << std::endl;
	return 0;
}