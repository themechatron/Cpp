#include "SkipList.h"

template<class T>
SkipList<T>::SkipList(int _level = 1)
{
	level = _level;
	elements = 0;
	head = new Node();
	tail = new Node();
	//connect the head and the tail
	head->right = tail;
	tail->left = head;
}

template<class T>
SkipList<T>::SkipList(const SkipList<T>& other)
{
	copy(other.head, other.tail, other.level, other.elements);
}

template<class T>
SkipList<T>& SkipList<T>::operator=(const SkipList<T>& other)
{
	if (this != &other){
		freeNodes(head, tail);
		copy(other.head, other.tail, other.level, other.elements);
	}
	return *this;
}

template<class T>
void SkipList<T>::insert(const T& value)
{
	insertPrivate(value);
}

template<class T>
void SkipList<T>::print() const
{
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
bool SkipList<T>::contains(const T& value)
{
	if (elements == 0){
		return false;
	}
	Node* printerHead = head;
	Node* printerTail = tail;

	//go to the highest level
	for (int i = 1; i < level; i++){
		printerHead = printerHead->up;
		printerTail = printerTail->up;
	}

	Node* walker = printerHead;
	while (true){
		if (walker->right != nullptr && walker->right != printerTail){
			if (walker->right->data == value){
				return true;
			}
			if (walker->right->data < value){
				walker = walker->right;
				continue;
			}
		}
		if (walker->left != nullptr && walker->left != printerHead){
			if (walker->left->data == value){
				return true;
			}
			if (walker->left->data > value){
				walker = walker->left;
				continue;
			}
		}
		if (walker->left != nullptr && walker->left != printerHead && walker->left->data > value){

		}
		if (walker->down != nullptr){
			walker = walker->down;
			printerHead = printerHead->down;
			printerTail = printerTail->down;
			continue;
		}
		if (walker->down == nullptr){
			return false;
		}
	}
}

template<class T>
void SkipList<T>::remove(const T& value)
{
	if (!contains(value)){
		return;
	}
	elements--;
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
SkipList<T>& SkipList<T>::merge(SkipList<T>& other)
{
	SkipList<T>* result = new SkipList<T>;
	SkipList<T> temp; // find the bigger SkipList by level
	if (level >= other.level){
		result->copy(head, tail, level, elements);
		temp = other;
	}
	else{
		result->copy(other.head, other.tail, other.level, other.elements);
		temp = *this;
	}
	Node* resultHead = result->head;
	Node* resultTail = result->tail;
	Node* walkerHead = temp.head;
	Node* walkerTail = temp.tail;

	//find how many times each number is repeated and put it into vector
	//very complex :( | O(n^3)
	vector<int> numbers;
	vector<int> repetitions;
	while (true){
		Node* copier = walkerHead;
		while (copier != nullptr && copier->right != nullptr && copier->right != walkerTail){
			copier = copier->right;
			if (!result->contains(copier->data)){
				if (find(numbers.begin(), numbers.end(), copier->data) == numbers.end()){
					numbers.push_back(copier->data);
					repetitions.push_back(1);
				}
				else{
					for (size_t j = 0; j < numbers.size(); ++j){
						if (numbers[j] == copier->data){
							repetitions[j]++;
						}
					}
				}

			}
		}
		if (walkerHead->up != nullptr && walkerTail->up != nullptr){
			walkerHead = walkerHead->up;
			walkerTail = walkerTail->up;
		}
		else{
			break;
		}
	}

	//the actual merging
	//we found the nodes that are not contained in the first skip list
	//now we are going to insert them into our result
	for (size_t i = 0; i < numbers.size(); ++i){
		result->insertPrivate(numbers[i], repetitions[i]); //using the private function insert we insert the element repetitions[i] times
	}

	return *result;
}

template<class T>
SkipList<T>& SkipList<T>::intersect(SkipList<T>& other)
{
	SkipList<T>* result = new SkipList<T>;

	Node* otherHead = other.head;
	Node* otherTail = other.tail;

	vector<int> numbers;
	vector<int> repetitions;
	while (true){
		Node* copier = otherHead;
		while (copier != nullptr && copier->right != nullptr && copier->right != otherTail){
			copier = copier->right;
			if (find(numbers.begin(), numbers.end(), copier->data) == numbers.end()){
				numbers.push_back(copier->data);
				repetitions.push_back(1);
			}
			else{
				for (size_t j = 0; j < numbers.size(); ++j){
					if (numbers[j] == copier->data){
						repetitions[j]++;
					}
				}
			}
		}
		if (otherHead->up != nullptr && otherTail->up != nullptr){
			otherHead = otherHead->up;
			otherTail = otherTail->up;
		}
		else{
			break;
		}
	}

	//check the actual level of our new skip list
	int lev = 1;
	for (size_t i = 1; i < numbers.size(); ++i){
		if (contains(numbers[i]) && other.contains(numbers[i])){
			lev++;
		}
	}

	//create nodes for our skip list
	for (int i = 1; i <= lev; i++){
		if (i == result->level){
			Node* upHead = result->head;
			Node* upTail = result->tail;
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
			result->level++; //increase the current level
		}
	}

	//the actual intersect
	//we found the nodes that are contained in the first skip list and the second skip list
	//now we are going to insert them into our result
	for (size_t i = 0; i < numbers.size(); ++i){
		if (contains(numbers[i]) && other.contains(numbers[i])){
			result->insertPrivate(numbers[i], repetitions[i]); //using the private function insert we insert the element repetitions[i] times
		}
	}

	return *result;
}

template<class T>
SkipList<T>::~SkipList()
{
	freeNodes(head, tail);
}

template<class T>
void SkipList<T>::copy(Node* _head, Node* _tail, int _level, int _elements)
{
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

	//connect all the up and down nodes together
	copyHead = head;
	copyTail = tail;
	for (int i = 1; i < level; i++){
		Node* cpy = copyHead;
		if (i <= 1){
			while (cpy->right != nullptr && cpy->right != copyTail){
				cpy = cpy->right;
			}
			copyHead = copyHead->up;
			copyTail = copyTail->up;
			continue;
		}
		Node* headCopy = copyHead->down;
		Node* tailCopy = copyTail->down;
		while (cpy->right != nullptr && cpy->right != copyTail){
			cpy = cpy->right;
			while (headCopy->right != nullptr && headCopy->right != tailCopy){
				headCopy = headCopy->right;
				if (headCopy->data == cpy->data){
					headCopy->up = cpy;
					cpy->down = headCopy;
					break;
				}
			}
		}
		copyHead = copyHead->up;
		copyTail = copyTail->up;
	}
}

template<class T>
void SkipList<T>::freeNodes(Node* _head, Node* _tail)
{
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

template<class T>
void SkipList<T>::insertPrivate(const T& value, int _level = -1)
{
	//TODO optimization
	if (contains(value)){
		return;
	}
	elements++;
	if (_level == -1){ //if the level is -1 this means that we use the default value and it is invalid and we need to generate random level
		_level = generateLevel();
	}
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

	Node* upHead = head;
	Node* upTail = tail;
	//add nodes with the same value in the snop
	for (int i = 1; i < _level; i++){
		//create the next node in the snop
		Node* hook = temp;
		temp->up = new Node(temp->data);
		temp->up->down = temp;
		temp = temp->up;
		upHead = upHead->up;
		upTail = upTail->up;
		//find the most left node that can go up
		while (hook->left != nullptr){
			if (hook->left->up != nullptr){
				hook = hook->left;
				break;
			}
			hook = hook->left;
		}

		//connect our new node the one that can go up and it's right node
		if (hook == upHead->down){
			temp->left = upHead;
			if (upHead->right != upTail){
				temp->right = upHead->right;
				upHead->right->left = temp;
				upHead->right = temp;
			}
			else{
				temp->right = upTail;
				upTail->left = temp;
				upHead->right = temp;
			}
		}
		else{
			temp->left = hook->up;
			if (hook->up->right != upTail){
				temp->right = hook->up->right;
				hook->up->right->left = temp;
				hook->up->right = temp;
			}
			else{
				temp->right = upTail;
				upTail->left = temp;
				hook->up->right = temp;
			}
		}
	}
}
