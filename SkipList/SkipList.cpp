#include "SkipList.h"
template<class T>
SkipList<T>::SkipList(int _level = 1){
	level = _level;
	head = new Node();
	tail = new Node();
	//connect the head and the tail
	head->right = tail;
	tail->left = head;
}

template<class T>
void SkipList<T>::insert(const T& value){
	if (contains(value)){
		return;
	}
	int _level = generateLevel(); //generates a random level
	if (_level == level && level < MAX_LEVEL){
		Node* upHead = head;
		Node* upTail = tail;
		while (upHead->up != nullptr && upTail->up != nullptr){
			upHead = upHead->up;
			upTail = upTail->up;
		}
		upHead->up = new Node(); //create new node in the head because the level was increased
		upTail->up = new Node(); //create new node in the tail because the level was increased
		//connect the new created nodes
		upHead = upHead->up;
		upTail = upTail->up;
		upTail->left = upHead;
		upHead->right = upTail;
		level++; //increase the current level
	}

	Node* dummy = head;
	while (dummy->right != nullptr && dummy->right->data < value && dummy->right != tail){
		dummy = dummy->right; //find the place to insert
	}
	Node* temp = new Node(value); //create new node for the value we want to add
	//connect it to the other nodes
	temp->left = dummy;
	temp->right = dummy->right;
	dummy->right->left = temp;
	dummy->right = temp;

	//add nodes with the same value in the snop
	for (int i = 1; i < _level; i++){
		//create the next node in the snop
		Node* hook = temp;
		temp->up = new Node(temp->data);
		temp->up->down = temp;
		temp = temp->up;

		//find the most left node that can go up
		while (hook->left != nullptr){
			if (hook->left->up != nullptr){
				hook = hook->left;
				break;
			}
			hook = hook->left;
		}

		//connect our new node the one that can go up and it's right node
		temp->left = hook->up;
		temp->right = hook->up->right;
		hook->up->right->left = temp;
		hook->up->right = temp;
	}
}

template<class T>
bool contains(const T& value){
	return false;
}
