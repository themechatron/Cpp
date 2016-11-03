#include<iostream>
using namespace std;

//c++ 11
auto sum = [](int x, int y){ return x + y; }; 
auto difference = [](int x, int y){ return x - y; };
auto mult = [](int x, int y){ return x * y; };
auto devide = [](int x, int y){ return x / y; };
//c++ 14 [](auto x, auto y){..}


template<class T,class U>
auto asd = [](T x, U y) const{ return x + y; };
int main(){

	cout << asd(3, 4);
	system("pause");
	return 0;
}