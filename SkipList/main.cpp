#include "SkipList.h"

int main(){
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
	cout << pesho.contains(99) << endl;
	cout << gosho.contains(10000) << endl;


	SkipList<int> merge1;
	for (size_t i = 0; i < 16; i++)
	{
		merge1.insert(i);
	}
	SkipList<int> merge2;
	for (size_t i = 15; i < 20; i++)
	{
		merge2.insert(i);
	}

	cout << "lllllllllllllLLLLLLLLLLLLLLLLLLLLLLlllllllllll" << endl;
	merge1.print();
	cout << "lllllllllllllLLLLLLLLLLLLLLLLLLLLLLlllllllllll" << endl;
	merge2.print();
	cout << "lllllllllllllLLLLLLLLLLLLLLLLLLLLLLlllllllllll" << endl;

	SkipList<int> aaa = merge1.merge(merge2);


	cout << "lllllllllllllLLLLLLLLLLLLLLLLLLLLLLlllllllllll" << endl;
	merge1.print();
	cout << "lllllllllllllLLLLLLLLLLLLLLLLLLLLLLlllllllllll" << endl;
	merge2.print();
	cout << "lllllllllllllLLLLLLLLLLLLLLLLLLLLLLlllllllllll" << endl;

	cout << "--------------------" << endl;
	aaa.print();
	aaa.insert(100000);
	aaa.remove(5);
	cout << endl;
	aaa.print();
	cout << "--------------------" << endl;
	cout << endl;
	cout << "lllllllllllllLLLLLLLLLLLLLLLLLLLLLLlllllllllll" << endl;
	merge1.print();
	cout << "lllllllllllllLLLLLLLLLLLLLLLLLLLLLLlllllllllll" << endl;
	merge2.print();
	cout << "lllllllllllllLLLLLLLLLLLLLLLLLLLLLLlllllllllll" << endl;
	cout << "INTERSECT" << endl;
	SkipList<int> bbb = merge2.intersect(merge1);
	bbb.print();
	bbb.insert(9999);
	bbb.remove(6);
	cout << "==========" << endl;
	bbb.print();
	cout << "--------------------" << endl;

	SkipList<int>::SkipListIterator it = zaki.begin();
	for (it = zaki.begin(); it != zaki.end(); ++it){
		cout << "AAA iterator" << endl;
	}

	
	return 0;
}
