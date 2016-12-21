#include "SkipList.h"

int main()
{
	cout << std::boolalpha;
	srand(time(NULL));
	SkipList<int> zaki;
	for (int i = -100; i<100; i++){
		zaki.insert(i);
	}
	zaki.print();
	cout << endl;
	for (int i = -100; i<100; i++){
		//cout << "Contains: " << zaki.contains(i) << endl;
	}
	for (int i = -10; i<9; i++){
		zaki.remove(i);
	}
	zaki.print();
	cout << endl;
	for (int i = -100; i<100; i++){
		//cout << "Contains: " << zaki.contains(i) << endl;
	}
	zaki.insert(1000);

	cout << "Done!" << endl;
	SkipList<int> pesho = zaki;
	for (int i = -10; i<9; i++){
		pesho.insert(i);
	}
	pesho.print();
	cout << pesho.contains(1) << endl;

	cout << endl;
	SkipList<int> gosho;
	gosho = pesho;
	gosho.print();
	cout << gosho.contains(99) << endl;
  
	return 0;
}
