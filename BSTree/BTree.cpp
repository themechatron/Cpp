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
T& BTree<T>::getElement(const char* s) const{
	return privateGetElement(root, s);
}

template<class T>
void BTree<T>::inOrder() const{
	privateInOrder(root);
}

template<class T>
void BTree<T>::preOrder() const{
	privatePreOrder(root);
}

template<class T>
void BTree<T>::postOrder() const{
	privatePostOrder(root);
}

template<class T>
vector<T> BTree<T>::listLeaves() const{
	vector<T> leaves;
	privateListLeaves(root, leaves);
	return leaves;
}

template<class T>
bool BTree<T>::contains(const T& element) const{
	bool result = false;
	privateContains(root, element, result);
	return result;
}

template<class T>
string BTree<T>::findTrace(const T& element) const{
	if (!contains(element)){
		return "_";
	}
	string result = "";
	privateFindTrace(root, result, element);
	return result;
}

template<class T>
void BTree<T>::prettyPrint() const{
	privatePrettyPrint(root, 0);
}

template<class T>
void BTree<T>::serealize(string filename) const{
	ofstream file(filename.c_str());
	privateSerealize(file, root);
}

template<class T>
T& BTree<T>::operator[](int index) const{
	T result;
	privateOperatorFind(root, index, result,1);
	return result;
}

template<class T>
vector<T> BTree<T>::level(int k) const{
	vector<T> result;
	privateLevel(root, result, k, 0);
	return result;
}

template<class T>
BTree<T>::~BTree(){
	freeNode(root);
}

//private methods
template<class T>
auto BTree<T>::navigate(const T& _key, Node*& _root) const -> Node*&{
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
T& BTree<T>::privateGetElement(Node* _root, const char* s) const{
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

template<class T>
void BTree<T>::privateInOrder(Node* _root) const{
	if (_root == nullptr){
		return;
	}
	privateInOrder(_root->left);
	cout << _root->key << " ";	
	privateInOrder(_root->right);
}

template<class T>
void BTree<T>::privatePreOrder(Node* _root) const{
	if (_root == nullptr){
		return;
	}
	cout << _root->key << " ";
	privatePreOrder(_root->left);
	privatePreOrder(_root->right);
}

template<class T>
void BTree<T>::privatePostOrder(Node* _root) const{
	if (_root == nullptr){
		return;
	}
	privatePostOrder(_root->left);
	privatePostOrder(_root->right);
	cout << _root->key << " ";
}

template<class T>
void BTree<T>::privateListLeaves(Node* _root, vector<T>& leaves) const{
	if (_root != nullptr && _root->left == nullptr && _root->right == nullptr){
		leaves.push_back(_root->key);
	}
	if (_root == nullptr){
		return;
	}
	privateListLeaves(_root->left, leaves);
	privateListLeaves(_root->right, leaves);
}

template<class T>
void BTree<T>::privateContains(Node* _root, const T& element, bool& result) const{
	if (_root == nullptr){
		return;
	}
	if (_root->key == element){
		result = true;
		return;
	}
	privateContains(_root->left, element, result);
	privateContains(_root->right, element, result);
}

template<class T>
void BTree<T>::privateFindTrace(Node* _root, string& trace, const T& number) const{
	if (_root == nullptr || _root->key == number){
		return;
	}
	if (_root->key < number){
		trace += "L";
		privateFindTrace(_root->left, trace, number);
	}
	else{
		trace += "R";
		privateFindTrace(_root->right, trace, number);
	}
}

template<class T>
void BTree<T>::privatePrettyPrint(Node* _root, size_t position) const{
	if (_root == nullptr){
		return;
	}
	privatePrettyPrint(_root->left, ++position);
	for (size_t i = 0; i < position; i++)
	{
		cout << "\t";
	}
	cout << _root->key << endl;
	privatePrettyPrint(_root->right, ++position);
}  

template<class T>
void BTree<T>::privateSerealize(ofstream& file, Node* _root) const{
	if (_root == nullptr){
		file << "()";
		return;
	}
	file << "(" << _root->key;
	privateSerealize(file, _root->left);
	file << ")";
	privateSerealize(file, _root->right);
	file << ")";
}

template<class T>
void BTree<T>::privateOperatorFind(Node* _root, int index, T& result, int previous) const {
	if (index == 0 && _root != nullptr){
		result = _root->key;
		return;
	}
	if (_root == nullptr){
		result = root->key;
		return;
	}
	if (previous == 1){
		privateOperatorFind(_root->left, index - 1, result, previous + 1);
	}
	if (previous == 2){
		privateOperatorFind(_root->left, index - 1, result, previous - 1);
	}
}

template<class T>
void BTree<T>::privateLevel(Node* _root, vector<T>& result, int k, int current) const{
	if (_root == nullptr || k < 0){
		return;
	}
	if (current == k){
		result.push_back(_root->key);
		return;
	}
	privateLevel(_root->left, result, k, current + 1);
	privateLevel(_root->right, result, k, current + 1);
}