#include <iostream>
#include<stdlib.h>
#include<ctime>

using namespace std;

#define MAX_LEVEL 32
#define PROB 0.25
;
template<class T>
class SkipList{
private:
	struct Node{
		T data;
		Node* left, *right, *up, *down;
		Node(const T& _data = T(), Node* _left = nullptr, Node* _right = nullptr, Node* _up = nullptr, Node* _down = nullptr)
			:data(_data), left(_left), right(_right), up(_up), down(_down){}
	};
	Node* head;
	Node* tail;
	int level;
	int elements;
public:
	SkipList(int _level = 1);
	SkipList(const SkipList<T>& other);
	SkipList<T>& operator=(const SkipList<T>& other);
	void insert(const T& value);
	void print() const;
	bool contains(const T& value);
	void remove(const T& value);
	~SkipList();
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
	void copy(Node* _head, Node* _tail, int _level, int _elements);
	void freeNodes(Node* _head, Node* _tail);
};
