#include "BTree.h"

//public methods
template<class T>
BTree<T>::BTree() :root(nullptr), size(0){}

template<class T>
void BTree<T>::add(const T& _key){
	Node*& toAdd = navigate(_key, root);
	if (toAdd == nullptr){
		toAdd = new Node(_key);
		size++;
	}
}

template<class T>
void BTree<T>::remove(const T& _key){
	Node*& exist = navigate(_key, root);
	if (exist == nullptr){
		return;
	}
	Node* toRemove = exist;
	Node* connect = exist->right;
	if (connect == nullptr){
		connect = exist->left; //If the node does not have left child it must point to the right child.
	}
	else{
		Node* leftmost = exist->right;
		while (leftmost->left != nullptr) {
			leftmost = leftmost->left;
		}
		leftmost->left = exist->left;
	}
	exist = connect;
	delete toRemove;
}

template<class T>
void BTree<T>::print() const{
	privatePrint(root);
}

template<class T>
size_t BTree<T>::count() const{
	return size;
}

template<class T>
size_t BTree<T>::evens() const {
	size_t result = 0;
	privateEvens(root, result);
	return result;
}

template<class T>
size_t BTree<T>::searchCount(bool(*predicate)(const T&)) const{
	size_t result = 0;
	privateSearchCount(predicate, root, result);
	return result;
}

template<class T>
size_t BTree<T>::height() const{
	return privateHeight(root);
}

template<class T>
size_t BTree<T>::leaves() const{
	size_t result = 0;
	privateLeaves(root, result);
	return result;
}

template<class T>
int BTree<T>::maxLeave() const{
	if (root == nullptr){
		return 0;
	}
	if (root->left == nullptr && root->right == nullptr){
		return root->key;
	}
	return privateMaxLeave(root, root->key);
}

template<class T>
T& BTree<T>::getElement(const char* s){
	return privateGetElement(root, s);
}

template<class T>
BTree<T>::~BTree(){
	freeNode(root);
}

//private methods
template<class T>
auto BTree<T>::navigate(const T& _key, Node*& _root) -> Node*&{
	if (_root == nullptr || _root->key == _key){
		return _root;
	}
	if (_root->key < _key){
		return navigate(_key, _root->left);
	}
	if (_root->key > _key){
		return navigate(_key, _root->right);
	}
}

template<class T>
void BTree<T>::privatePrint(Node* _root) const{
	if (_root == nullptr){
		return;
	}
	privatePrint(_root->left);
	cout << _root->key << " ";
	privatePrint(_root->right);
}

template<class T>
void BTree<T>::privateEvens(Node* _root, size_t& result) const{
	if (_root == nullptr){
		return;
	}
	if (_root->key % 2 == 0){
		result++;
	}
	privateEvens(_root->left, result);
	privateEvens(_root->right, result);
}

template<class T>
void BTree<T>::privateSearchCount(bool(*predicate)(const T&), Node* _root, size_t& result) const{
	if (_root == nullptr){
		return;
	}
	if (predicate(_root->key)){
		result++;
	}
	privateSearchCount(predicate, _root->left, result);
	privateSearchCount(predicate, _root->right, result);
}

template<class T>
size_t BTree<T>::privateHeight(Node* _root) const{
	if (_root == nullptr){
		return 0;
	}
	return 1 + max(privateHeight(_root->left), privateHeight(_root->right));
}

template<class T>
void BTree<T>::privateLeaves(Node* _root, size_t& result) const{
	if (_root != nullptr && _root->left == nullptr && _root->right == nullptr){
		result++;
	}
	if (_root == nullptr){
		return;
	}
	privateLeaves(_root->left, result);
	privateLeaves(_root->right, result);
}

template<class T>
int BTree<T>::privateMaxLeave(Node* _root, int max) const{
	if (_root == nullptr){
		return max;
	}
	if (max < _root->key){
		max = _root->key;
	}
	return privateMaxLeave(_root->left, max);
	return privateMaxLeave(_root->right, max);
}

template<class T>
T& BTree<T>::privateGetElement(Node* _root, const char* s){
	if (_root == nullptr){
		cout << "No element match!" << endl;
		return _root->key;
	}
	if (*s == NULL && _root != nullptr){
		return _root->key;
	}
	if (*s == 'L'){
		if (_root->left == nullptr){
			cout << "No element match!" << endl;
			return _root->key;
		}
		return privateGetElement(_root->left, s + 1);
	}
	if (*s == 'R'){
		if (_root->right == nullptr){
			cout << "No element match!" << endl;
			return _root->key;
		}
		return privateGetElement(_root->right, s + 1);
	}
}

template<class T>
void BTree<T>::freeNode(Node* _root){
	if (_root == nullptr){
		return;
	}
	freeNode(_root->left);
	freeNode(_root->right);
	delete _root;
}