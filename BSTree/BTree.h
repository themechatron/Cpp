#pragma once
#include <iostream>
#include <algorithm>
using std::cout;
using std::endl;
using std::max;

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
	void print() const;
	size_t count() const;
	size_t evens() const;
	size_t searchCount(bool(*)(const T&)) const;
	size_t height() const;
	size_t leaves() const;
	int maxLeave() const;
	T& getElement(const char*);
	~BTree();
private:
	Node*& navigate(const T&, Node*&);
	void privatePrint(Node*) const;
	void privateEvens(Node*, size_t&) const;
	void privateSearchCount(bool(*)(const T&), Node*, size_t&) const;
	size_t privateHeight(Node*) const;
	void privateLeaves(Node*, size_t&) const;
	int privateMaxLeave(Node*, int) const;
	T& privateGetElement(Node*, const char*);
	void freeNode(Node*);
};
