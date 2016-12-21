#include "SkipList.h"
template<class T>
SkipList<T>::SkipList(int _level = 1){
	level = _level;
	elements = 0;
	head = new Node();
	tail = new Node();
	//connect the head and the tail
	head->right = tail;
	tail->left = head;
}

template<class T>
SkipList<T>::SkipList(const SkipList<T>& other){
	copy(other.head, other.tail, other.level, other.elements);
}

template<class T>
SkipList<T>& SkipList<T>::operator=(const SkipList<T>& other){
	if (this != &other){
		freeNodes(head, tail);
		copy(other.head, other.tail, other.level, other.elements);
	}
	return *this;
}

template<class T>
void SkipList<T>::insert(const T& value){
	//TODO optimization
	if (contains(value)){
		return;
	}
	elements++;
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

		//connect the created nodes
		upHead->up->down = upHead;
		upTail->up->down = upTail;
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
void SkipList<T>::print()const{
	//TODO optimization
	Node* printer = head;
	Node* printerTail = tail;
	for (int i = 1; i<level; i++){
		Node* print = printer;
		cout << "Level " << i << ": ";
		while (print->right != nullptr && print->right != printerTail){
			cout << print->right->data << " ";
			print = print->right;
		}
		printer = printer->up;
		printerTail = printerTail->up;
		cout << endl;
	}
}

template<class T>
bool SkipList<T>::contains(const T& value){
	//TODO optimization
	Node* printerHead = head;
	Node* printerTail = tail;

	//go to the highest level
	for (int i = 1; i < level; i++){
		printerHead = printerHead->up;
		printerTail = printerTail->up;
	}

	//check if the value is contained on this level if not go to lower level if possible
	for (int i = 0; i < level; i++){
		Node* print = printerHead;
		while (print->right != nullptr && print->right != printerTail){
			if (print->right->data == value){
				return true;
			}
			print = print->right;
		}
		//we are sure that we can go down because we start from the highest current level and we iterate it to the level 1
		printerHead = printerHead->down;
		printerTail = printerTail->down;
	}
	return false;
}

template<class T>
void SkipList<T>::remove(const T& value){
	//TODO optimization
	if (!contains(value)){
		return;
	}
	Node* printerHead = head;
	Node* printerTail = tail;
	for (int i = 1; i < level; i++){
		printerHead = printerHead->up;
		printerTail = printerTail->up;
	}
	for (int i = 0; i<level; i++){
		Node* print = printerHead;
		while (print->right != nullptr && print->right != printerTail){
			if (print->right->data == value){
				print = print->right;

				//deleting the node and alocating the rest of the nodes
				print->left->right = print->right;
				print->right->left = print->left;

				if (print->down != nullptr){
					print->down->up = nullptr;
				}
				delete print;

				elements--;
				//break the loop
				break;
			}
			print = print->right;
		}
		printerHead = printerHead->down;
		printerTail = printerTail->down;
	}
}

template<class T>
SkipList<T>::~SkipList(){
	freeNodes(head, tail);
}

template<class T>
void SkipList<T>::copy(Node* _head, Node* _tail, int _level, int _elements){
	//set the default things
	head = new Node();
	tail = new Node();
	head->right = tail;
	tail->left = head;
	level = 1;
	elements = _elements;

	//increase the level and create all the nodes we needed for head and tail
	for (int i = 1; i < _level; i++){
		if (i == level){
			Node* upHead = head;
			Node* upTail = tail;
			while (upHead->up != nullptr && upTail->up != nullptr){
				upHead = upHead->up;
				upTail = upTail->up;
			}
			upHead->up = new Node(); //create new node in the head because the level was increased
			upTail->up = new Node(); //create new node in the tail because the level was increased

			//connect the created nodes
			upHead->up->down = upHead;
			upTail->up->down = upTail;
			upHead = upHead->up;
			upTail = upTail->up;
			upTail->left = upHead;
			upHead->right = upTail;
			level++; //increase the current level
		}
	}

	//real head and tail updater
	Node *copyHead = head;
	Node* copyTail = tail;

	//other head and tail updater
	Node* copyOtherHead = _head;
	Node* copyOtherTail = _tail;

	//copy all the values from other SkipList to our SkipList
	for (int i = 1; i < level; i++){
		Node* copy = copyOtherHead;
		Node* current = copyHead;

		//create the nodes one by one and connect them toghether
		while (copy->right != nullptr && copy->right != copyOtherTail){
			copy = copy->right;
			current->right = new Node(copy->data);
			current->right->left = current;
			current = current->right;
		}
		current->right = copyTail;
		copyTail->left = current;
		copyOtherHead = copyOtherHead->up;
		copyOtherTail = copyOtherTail->up;
		copyHead = copyHead->up;
		copyTail = copyTail->up;
	}
}

template<class T>
void SkipList<T>::freeNodes(Node* _head, Node* _tail){
	Node* deleteHead = _head;
	Node* deleteTail = _tail;
	//delete all the levels node by node
	for (int i = 0; i < level; i++){
		Node* deleter = deleteHead;
		while (deleter->right != nullptr && deleter->right != deleteTail && deleter != deleteHead){
			deleter = deleter->right;
			delete deleter->left;
		}
		deleteHead = deleteHead->up;
		deleteTail = deleteTail->up;
	}
	deleteHead = head;
	deleteTail = tail;

	//delete all the head up and tail up levels
	while (deleteHead->up != nullptr && deleteTail->up != nullptr){
		deleteHead = deleteHead->up;
		deleteTail = deleteTail->up;
		delete deleteHead->down;
		delete deleteTail->down;
	}
}
