#pragma once
#define MAX_HEIGHT 32
template<class T>
class SkipList
{
private:
	struct Node{
		T* value;
		Node* next;
		Node* previous;
	};
	int height;
	Node* head;
public:
	SkipList();
	~SkipList();
};

