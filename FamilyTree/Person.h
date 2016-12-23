#pragma once

#include<iostream>
#include<string>

using std::string;
using std::cout;
using std::endl;

struct Person{
	string egn;
	string name;
	string sex;
	int birthYear;
	int deathYear;
	Person* mother;
	Person* father;
	Person* child;
	Person(string _egn = "1234567890", std::string _name = "zaki", std::string _sex = "male", int _birthYear = 1996, int _deathYear = -1, Person* _mother = nullptr, Person* _father = nullptr, Person* _child = nullptr){
		egn = _egn;
		name = _name;
		sex = _sex;
		birthYear = _birthYear;
		deathYear = _deathYear;
		mother = _mother;
		father = _father;
		child = _child;
	}
};
