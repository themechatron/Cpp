#pragma once
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <fstream>

using std::cout;
using std::endl;
using std::max;
using std::vector;
using std::string;
using std::ofstream;
using std::ifstream;

template<class T>
class BTree{
private:
	struct Node{
		T key;
		Node* left;
		Node* right;
		Node(const T& _key, Node* _left = nullptr, Node* _right = nullptr) :key(_key), left(_left), right(_right){ }
	};
	Node* root;
	size_t size;
public:
	BTree();
	BTree(const BTree<T>&) = delete;
	BTree<T>& operator=(const BTree<T>&) = delete;
	void add(const T&);
	void remove(const T&);
	size_t count() const;
	size_t evens() const;
	size_t searchCount(bool(*)(const T&)) const;
	size_t height() const;
	size_t leaves() const;
	int maxLeave() const;
	T& getElement(const char*) const;
	void inOrder() const;
	void preOrder() const;
	void postOrder() const;
	vector<T> listLeaves() const;
	bool contains(const T&) const;
	string findTrace(const T&) const;
	void prettyPrint() const;
	void serealize(string) const;
	T& operator[](int) const;
	vector<T> level(int) const;
	~BTree();
private:
	Node*& navigate(const T&, Node*&) const;
	void privatePrint(Node*) const;
	void privateEvens(Node*, size_t&) const;
	void privateSearchCount(bool(*)(const T&), Node*, size_t&) const;
	size_t privateHeight(Node*) const;
	void privateLeaves(Node*, size_t&) const;
	int privateMaxLeave(Node*, int) const;
	T& privateGetElement(Node*, const char*) const;
	void privateInOrder(Node*) const;
	void privatePreOrder(Node*) const;
	void privatePostOrder(Node*) const;
	void privateListLeaves(Node*, vector<T>&) const;
	void privateContains(Node*, const T&, bool&) const;
	void privateFindTrace(Node*, string&, const T&) const;
	void privatePrettyPrint(Node* root, size_t position) const;
	void privateSerealize(ofstream&, Node*) const;
	void privateOperatorFind(Node*, int, T&, int) const;
	void privateLevel(Node*,vector<T>& , int, int) const;
	void freeNode(Node*);
};
