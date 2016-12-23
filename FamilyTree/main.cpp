#include "FamilyTree.h"

int main(){
	Person* gosho = new Person("1122331111", "gosho", "male", 1980);
	FamilyTree zaki(gosho);
	Person* goshoMother = new Person("2244222222", "penka", "female", 1953);
	Person* goshoFather = new Person("3309333333", "ivan", "male", 1953);
	Person* goshoMotherMother = new Person("9609173427", "zdravko", "female", 1953);
	Person* goshoMotherFather = new Person("6710053600", "liuben", "male", 1953);
	zaki.recordParents("1122331111", goshoFather, goshoMother);
	zaki.recordParents("2244222222", goshoMotherMother, goshoMotherFather);
	zaki.recordParents("3309333333", goshoMotherFather, goshoMotherMother);
	//zaki.recordParents("9609173427", goshoFather, goshoMotherFather); // ok it works!
	zaki.printTree();

	cout << "The oldest person: ";
	Person* tito = zaki.oldestRelative();
	cout << tito->name << endl;
	cout << "The most common name: " << zaki.mostCommonName() << endl;
	vector<Person*> names = zaki.femalePredecessors();
	for (auto i = names.begin(); i != names.end(); ++i){
		cout << (*i)->name << endl;
	}
	cout << "Relationship: " << zaki.relationship(goshoMotherFather) << endl;

	map<string, unsigned int> hashedNames = zaki.commonNames();
	cout << "Hashed names: " << endl;
	for (auto it = hashedNames.begin(); it != hashedNames.end(); ++it){
		cout << "The name " << it->first << " is repeated " << it->second << " times" << endl;
	}

	FamilyTree p = zaki;
	p.printTree();

	FamilyTree x;
	x = zaki;

	cout << endl;
	x.printTree();

	return 0;
}