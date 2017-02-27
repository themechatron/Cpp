#include "HashTable.cpp"

int main(){
	HashMap<string, int> p;
	p["abc"] = 3;
	p["gosho"] = 2;
	p["goshodddddd"] = 4;
	p["goshodddddddd"] = 5;
	p["gosho"] = 7;
	p["goshodddddd"] = 7;
	p["goshodddddddd"] = 7;
	cout<<p["abc"]<<endl;
	cout<<p["gosho"]<<endl;
	cout<<p["goshodddddd"]<<endl;
	cout<<p["goshodddddddd"]<<endl;

	return 0;
}	