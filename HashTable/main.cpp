#include "HashTable.h"

int main(){
	HashMap<string, int> p;
	p["abc"] = 3;
	p["gosho"] = 2;
	p["goshodddddd"] = 4;
	p["goshodddddddd"] = 5;
	cout<<p["abc"]<<endl;
	cout<<p["gosho"]<<endl;
	cout<<p["goshodddddd"]<<endl;
	cout<<p["goshodddddddd"]<<endl;

	return 0;
}	