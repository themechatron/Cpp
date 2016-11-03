#include<iostream>
using namespace std;

//c++ 11
auto sum = [](int x, int y){ return x + y; }; 
auto difference = [](int x, int y){ return x - y; };
auto mult = [](int x, int y){ return x * y; };
auto devide = [](int x, int y){ return x / y; };
//c++ 14 [](auto x, auto y){..}

int main(){
	return 0;
}