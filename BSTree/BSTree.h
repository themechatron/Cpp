#ifndef BSTREE_H
#define BSTREE_H

#include <iostream>
#include <vector>
#include <assert.h>
template <typename T>
struct Node {
	T data;
	Node* left;
	Node* right;
	Node(T data, Node* left = nullptr, Node* right = nullptr) : data(data), left(left), right(right) {}
};

template <typename T>
class BSTree
{
	Node<T>* root;

public:
	BSTree();
	BSTree(const BSTree<T>&);
	BSTree<T>& operator=(const BSTree<T>&);
	virtual ~BSTree();
	bool contains(const T&) const; //contains? element
	void add(const T&); //add element
	void remove(const T&); //remove element
	void print() const; //print method
	std::vector<T> preorderTraversal() const;
	std::vector<T> inorderTraversal() const;
	std::vector<T> postorderTraversal() const;
	BSTree<T>* reconstruct(const std::vector<T>&, const std::vector<T>&);
	int getHeight(Node<T>*) const; //gets the height
	Node<T>* copy(Node<T>*); //copy constructor helper
	std::vector<T> listLeaves();
	void serealize() const; //current prints in console, not in file
	BSTree<T>* deserealize(std::string); // currently reading from the console, not from file
	T& operator[](int idx);
protected:
private:
	void deleteAll(Node<T>*);
	Node<T>*& find(const T&, Node<T>*&);
	void print(Node<T>*, int) const;
	void preorderTraverse(Node<T>*, std::vector<T>&) const;
	void inorderTraverse(Node<T>*, std::vector<T>&) const;
	void postorderTraverse(Node<T>*, std::vector<T>&) const;
	Node<T>* reconstructNodes(const std::vector<T>&, const std::vector<T>&);
	int getHeight() const;
	void get_leaves(std::vector<T>&, Node<T>*);
	bool is_leaf(Node<T>*) const;
	void serealize(Node<T>*) const;
	T& find_element_by_index(int, int, Node<T>*);
};

template <typename T>
BSTree<T>::BSTree() :root(nullptr) {}

template<class T>
Node<T>* BSTree<T>::copy(Node<T>* other){
	if (other == nullptr){
		return nullptr;
	}
	Node<T>* copyNode = new Node<T>(other->data);
	copyNode->left = copy(other->left);
	copyNode->right = copy(other->right);
	return newNode;
}

template <typename T>
BSTree<T>::BSTree(const BSTree<T>& other) {
	root = copy(other.root);
}

template <typename T>
BSTree<T>& BSTree<T>::operator=(const BSTree<T>& other) {
	if (this != &other){
		delete_tree(root);
		Node *root = copy(other.root);
	}
	return *this;
}

template <typename T>
BSTree<T>::~BSTree() {
	deleteAll(root);
}

template <typename T>
void BSTree<T>::deleteAll(Node<T>* node) {
	if (node == nullptr) {
		return;
	}
	deleteAll(node->left);
	deleteAll(node->right);
	delete node;
}

template <typename T>
Node<T>*& BSTree<T>::find(const T& el, Node<T>*& node) {
	if (node == nullptr || node->data == el) {
		return node;
	}
	if (node->data < el) {
		return find(el, node->right);
	}
	return find(el, node->left);
}

template <typename T>
bool BSTree<T>::contains(const T& el) const {
	return find(el, root) != nullptr;
}

template <typename T>
void BSTree<T>::add(const T& el) {
	Node<T>*& existing = find(el, root);
	if (existing == nullptr) {
		existing = new Node<T>(el);
	}
}

template <typename T>
void BSTree<T>::remove(const T& el) {
	Node<T>*& existing = find(el, root);
	if (existing == nullptr) {
		// nothing to do
		return;
	}
	// find rightmost node of left child
	// and attach the right child to it
	Node<T>* toDelete = existing;
	Node<T>* replacement = existing->left;
	if (replacement == nullptr) {
		replacement = existing->right;
	}
	else {
		Node<T>* rightmost = existing->left;
		while (rightmost->right != nullptr) {
			rightmost = rightmost->right;
		}
		rightmost->right = existing->right;
	}
	// This will update the pointer in the parent because existing is a reference
	existing = replacement;
	// this deletes the old pointer
	delete toDelete;
}

template <typename T>
void BSTree<T>::print() const {
	print(root, 0);
}
template <typename T>
void BSTree<T>::print(Node<T>* node, int indent) const {
	if (node == nullptr) {
		return;
	}
	print(node->right, indent + 1);
	for (int i = 0; i < indent; i++) {
		std::cout << '\t';
	}
	std::cout << node->data << std::endl;
	print(node->left, indent + 1);
}

template <typename T>
std::vector<T> BSTree<T>::preorderTraversal() const {
	std::vector<T> result;
	preorderTraverse(root, result);
	return result;
}

template <typename T>
void BSTree<T>::preorderTraverse(Node<T>* node, std::vector<T>& result) const {
	if (node == nullptr) {
		return;
	}
	result.push_back(node->data);
	preorderTraverse(node->left, result);
	preorderTraverse(node->right, result);
}

template <typename T>
std::vector<T> BSTree<T>::inorderTraversal() const {
	std::vector<T> result;
	inorderTraverse(root, result);
	return result;
}
template <typename T>
void BSTree<T>::inorderTraverse(Node<T>* node, std::vector<T>& result) const {
	if (node == nullptr) {
		return;
	}
	inorderTraverse(node->left, result);
	result.push_back(node->data);
	inorderTraverse(node->right, result);
}

template <typename T>
std::vector<T> BSTree<T>::postorderTraversal() const {
	std::vector<T> result;
	postorderTraverse(root, result);
	return result;
}
template <typename T>
void BSTree<T>::postorderTraverse(Node<T>* node, std::vector<T>& result) const {
	if (node == nullptr) {
		return;
	}
	postorderTraverse(node->left, result);
	postorderTraverse(node->right, result);
	result.push_back(node->data);
}

template<class T>
Node<T>* BSTree<T>::reconstructNodes(const std::vector<T>& inorder, const std::vector<T>& preorder){
	if (inorder.size() == 0){
		return nullptr;
	}
	T rootData = preorder[0];
	int rootIndex = findIdx(rootData, inorder);
	Node<T>* result = new Node<T>(rootData);
	result->left = reconstructNodes(getSubvector(inorder, 0, rootIndex),
		getsSubvector(preorder, 1, rootIndex)); // Обхождане на дадените вектори за реконструиране на дървото
	result->right = reconstructNodes(getSubvector(inorder, rootIndex + 1, inorder.size()),
		getSubvector(preorder, rootIndex + 1, preorder.size()));
	return result;
}

template<class T>
BSTree<T>* BSTree<T>::reconstruct(const std::vector<T>& inorder, const std::vector<T>& preorder){
	Node<T>* rootResult = reconstructNodes(inorder, preorder);
	return new BSTree<T>(rootResult);
}

template<class T>
std::vector<T> getSubvector(const std::vector<T>& vec, int from, int to){
	return std::vector<T>(vec, vec.begin() + from, vec.begin() + to);
}

template<class T>
int findIdx(const T& el, const std::vector<T>& vec){
	for (int i = 0; i < vec.size(); i++){
		if (el == vec[i]){
			return i;
		}
	}
	return -1;
}

template<class T>
int BSTree<T>::getHeight() const{
	return getHeight(root);
}

template<class T>
int BSTree<T>::getHeight(Node<T>* node) const{
	if (node == nullptr){ return 0; }
	return std::max(getHeight(node->left), getHeight(node->right));
}

template<class T>
bool BSTree<T>::is_leaf(Node<T>* node) const{
	if (node == nullptr){
		return false;
	}
	if (node->left == nullptr && node->right == nullptr){
		return true;
	}
	return false;
}

template<class T>
std::vector<T> BSTree<T>::listLeaves(){
	std::vector<T> result;
	get_leaves(result, root);
	return result;
}

template<class T>
void BSTree<T>::get_leaves(std::vector<T>& vec, Node<T>* node){
	if (node == nullptr){
		return;
	}
	vec.push_back(node->data);
	get_leaves(vec, node->left);
	get_leaves(vec, node->right);
}

template<class T>
void BSTree<T>::serealize(Node<T>* node) const{
	if (node == nullptr){
		cout << "() ";
		return;
	}
	cout << "(" << node->data << " ";
	serealize(node->right);
	serealize(node->left);
	cout << ")";
}
template<class T>
void BSTree<T>::serealize() const{
	serealize(root);
}

template<class T>
BSTree<T>* BSTree<T>::deserealize(std::string path){
	// TODO IMPLEMENTATION
}

template<class T>
T& BSTree<T>::operator[](int idx){
	T& result = find_element_by_index(idx, 0, root);
	return result;
}

template<class T>
T& BSTree<T>::find_element_by_index(int index, int start, Node<T>* node){
	if (index == start){
		return node->data;
	}
	if (node == nullptr){
		return;
	}
	if (start % 2 == 0){
		if (node->left != nullptr){
			find_element_by_index(index, start + 1, node->left);
		}
		else{
			find_element_by_index(index, start + 1, node->right);
		}
	}
	else{
		if (node->right != nullptr){
			find_element_by_index(index, start + 1, node->right);
		}
		else{
			find_element_by_index(index, start + 1, node->left);
		}
	}
	// need to be fixed
}
#endif // BSTREE_H
