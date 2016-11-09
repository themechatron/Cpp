#pragma once
#include<string>
#include<vector>
using namespace std;

template<class T>
struct Node{
	T data;
	Node<T>* left;
	Node<T>* right;
	Node<T>(T _data, Node<T>* _left = nullptr, Node<T>* _right = nullptr) : data(_data), left(_left), right(_right){ };
};

template<class T>
class BTree{
private:
	Node<T>* root;
	bool add_node(const int, Node<T>*&); //add element's helper
	Node<T>*& find(const int, Node<T>*&); //find element's adress
	void delete_tree(Node<T>*); //destructor helper
	Node<T>* copy(Node<T>*); //copy constructor helper
	void preorder(Node<T>*, std::vector<T>&) const;
	void inorder(Node<T>*, std::vector<T>&) const;
	void postorder(Node<T>*, std::vector<T>&) const;
	int getHeight(Node<T>*);
	static Node<T>* reconstructNodes(const std::vector<T>&, const std::vector<T>&);
public:
	BTree<T>();
	BTree<T>(const BTree<T>&); //copy constructor
	BTree<T>& operator=(const BTree<T>&); //operator =
	bool add(const int); //add element
	bool remove(const int); //remove element
	bool contains(const int); //contains element?
	std::vector<T> preorderTraversal() const;
	std::vector<T> inorderTraversal() const;
	std::vector<T> postorderTraversal() const;
	static BTree<T>* reconstruct(const std::vector<T>&, const std::vector<T>&);
	int getHeight() const;
	~BTree<T>(); //destructor
};
