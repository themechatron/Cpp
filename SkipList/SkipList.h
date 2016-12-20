#include <iostream>
#include<stdlib.h>
#include<ctime>

using namespace std;

#define MAX_LEVEL 32
#define PROB 0.25

template<class T>
class SkipList{
private:
	struct Node{
		T data;
		Node* left, *right, *up, *down;
		Node(const T& da = T(), Node*l = nullptr, Node* r = nullptr, Node* u = nullptr, Node* d = nullptr)
			:data(da), left(l), right(r), up(u), down(d){}
	};
	Node* head;
	Node* tail;
	int level;
public:
	SkipList(int _level = 1);
	void insert(const T& value);
	void print() const;
	bool contains(const T& value);
private:
	double drand(){
		return rand() / (RAND_MAX + 1.0);
	}
	int generateLevel(){
		int _level;
		for (_level = 1; drand() < PROB && _level < level; _level++){
		}
		return _level;
	}
};
