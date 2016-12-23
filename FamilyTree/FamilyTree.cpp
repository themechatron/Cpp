#include "FamilyTree.h"

FamilyTree::FamilyTree(Person* person = nullptr) :root(person){}

FamilyTree:FamilyTree(const FamilyTree& other){
	root = new Person();
	copy(root, other.root);
}

FamilyTree& FamilyTree : operator=(const FamilyTree& other){
	if (this != &other){
		deletePerson(root);
		root = new Person();
		copy(root, other.root);
	}
	return *this;
}

void FamilyTree::recordParents(string _egn, Person* _father, Person* _mother){
	recordParentsPrivate(_egn, _father, _mother, root);
}

Person* FamilyTree::oldestRelative(){
	Person* oldest = new Person();
	oldestRelativePrivate(root, oldest);
	return oldest;
}

string FamilyTree::mostCommonName() const{
	vector<string> names;
	vector<int> repetitions;
	mostCommonNamePrivate(root, names, repetitions);
	int max = repetitions[0];
	int index = 0;
	for (size_t i = 0; i < repetitions.size(); i++)
	{
		if (repetitions[i] > max){
			max = repetitions[i];
			index = i;
		}
	}
	return names[index];
}

void FamilyTree::printTree() const{
	privatePrintTree(root);
}

vector<Person*> FamilyTree::femalePredecessors() const{
	vector<Person*> female;
	femalePredecessorsPrivate(root, female);
	return female;
}

string FamilyTree::relationship(Person* relative)const{
	string result = "";
	if (!contains(relative->name)){
		result += "Non a relative";
	}
	else{
		if (relative == root){
			result += "Root";
		}
		else{
			relationshipPrivate(relative, relative, result);
		}
	}
	return result;
}

bool FamilyTree::contains(string name) const{
	return containsPrivate(root, name);
}

map<string, unsigned int> FamilyTree::commonNames() const{
	map<string, unsigned int> hashTable;
	commonNamesPrivate(root, hashTable);
	return hashTable;
}

void FamilyTree::recordParentsPrivate(string e, Person* f, Person* m, Person* c){
	if (c == nullptr){
		return;
	}
	if (c->egn == e){
		if (c->mother != nullptr && c->father != nullptr){
			cout << "The person already have mother and father!" << endl;
			return;
		}
		if (c == f || c == m || c->child == f || c->child == m){
			cout << "I don't think this is biologically possible!" << endl;
			return;
		}
		else{
			c->mother = m;
			c->father = f;
			m->child = c;
			f->child = c;
		}
	}
	recordParentsPrivate(e, f, m, c->father);
	recordParentsPrivate(e, f, m, c->mother);
}

void FamilyTree::oldestRelativePrivate(Person* r, Person*& oldest){
	if (r == nullptr){
		return;
	}
	if (r->birthYear < oldest->birthYear){
		oldest = r;
	}
	if (r->birthYear == oldest->birthYear){
		if (r->egn.substr(2, 2) < oldest->egn.substr(2, 2)){
			oldest = r; //if there are 2 or more people with the same birthYear check the months
		}
		if (r->egn.substr(2, 2) == oldest->egn.substr(2, 2)){
			if (r->egn.substr(4, 2) < oldest->egn.substr(4, 2)){
				oldest = r; // if the months are equal check the day
			}
		}

	}
	oldestRelativePrivate(r->father, oldest);
	oldestRelativePrivate(r->mother, oldest);
}

void FamilyTree::privatePrintTree(Person* r) const{
	if (r == nullptr){
		return;
	}
	privatePrintTree(r->mother);
	cout << r->name << endl;
	privatePrintTree(r->father);
}

void FamilyTree::mostCommonNamePrivate(Person* r, vector<string>& names, vector<int>& repetitions)const{
	if (r == nullptr){
		return;
	}
	if (find(names.begin(), names.end(), r->name) == names.end()){
		names.push_back(r->name);
		repetitions.push_back(1);
	}
	else{
		for (int i = 0; i < names.size(); ++i){
			if (names[i] == r->name){
				repetitions[i]++;
				break;
			}
		}
	}
	mostCommonNamePrivate(r->father, names, repetitions);
	mostCommonNamePrivate(r->mother, names, repetitions);
}

void FamilyTree::femalePredecessorsPrivate(Person* r, vector<Person*>& female) const{
	if (r == nullptr){
		return;
	}
	if (r->sex == "female"){
		female.push_back(r);
	}
	femalePredecessorsPrivate(r->father, female);
	femalePredecessorsPrivate(r->mother, female);
}

void FamilyTree::relationshipPrivate(Person* relative, Person* _relative, string& result)const{
	if (relative == root){
		return;
	}
	if (relative == _relative){
		if (relative->sex == "male"){
			result += "father";
		}
		else{
			result += "mother";
		}
	}
	else{
		string temp = result;
		result = "grand-";
		result += temp;
	}
	relationshipPrivate(relative->child, _relative, result);
}

bool FamilyTree::containsPrivate(Person* r, string _name) const{
	if (r == nullptr){
		return false;
	}
	if (r->name == _name){
		return true;
	}
	return containsPrivate(r->father, _name) || containsPrivate(r->mother, _name);
}

void FamilyTree::commonNamesPrivate(Person* r, map<string, unsigned int>& hash) const{
	if (r == nullptr){
		return;
	}
	auto it = hash.find(r->name);
	if (it == hash.end()){
		hash[r->name] = 1;
	}
	else{
		hash[r->name]++;
	}
	commonNamesPrivate(r->father, hash);
	commonNamesPrivate(r->mother, hash);
}

FamilyTree::~FamilyTree(){
	deletePerson(root);
}

void FamilyTree::deletePerson(Person* r){
	if (r == nullptr){
		return;
	}
	cout << r << endl;
	deletePerson(r->father);
	deletePerson(r->mother);
	delete r;
}

void FamilyTree::copy(Person*& r, Person* o){
	r = o;
}