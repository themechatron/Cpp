#pragma once

#include<vector>
#include<algorithm>
#include<map>

#include "Person.h

using std::vector;
using std::find;
using std::map;

class FamilyTree
{
private:
	Person* root;
public:
	FamilyTree(Person* person = nullptr);
	FamilyTree(const FamilyTree& other);
	FamilyTree& operator=(const FamilyTree& other);
	Person* oldestRelative();
	string mostCommonName() const;
	void printTree() const;
	vector<Person*> femalePredecessors() const;
	string relationship(Person* relative)const;
	bool contains(string name) const;
	map<string, unsigned int> commonNames() const;
	~FamilyTree();
private:
	void recordParentsPrivate(string e, Person* f, Person* m, Person* c);
	void oldestRelativePrivate(Person* r, Person*& oldest);
	void privatePrintTree(Person* r) const;
	void mostCommonNamePrivate(Person* r, vector<string>& names, vector<int>& repetitions)const;
	void femalePredecessorsPrivate(Person* r, vector<Person*>& female) const;
	void relationshipPrivate(Person* relative, Person* _relative, string& result)const;
	bool containsPrivate(Person* r, string _name) const;
	void commonNamesPrivate(Person* r, map<string, unsigned int>& hash) const;
	void deletePerson(Person* r);
	void copy(Person*& r, Person* o);
};
