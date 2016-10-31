#include <iostream>
#include <assert.h>
#include <string.h>
#include <algorithm>

using namespace std;

template <class T>
using mapFn = T(*)(const T&);

template <class T>
struct Node
{
	Node<T> *left, *right;
	T data;
	Node(const T& d, Node<T> *l, Node<T> *r) :left(l), right(r), data(d){}
	Node() :left(NULL), right(NULL){}
};

template <class T>
class BTree
{
private:
	Node<T> *root;
	void simplePrint(Node<T> *) const;
	bool add(const T&, const char *, Node<T>*&);
	void deleteAll(Node<T> *);
	bool member(const T&, Node<T> *) const;
	void map(mapFn<T>, Node<T> *);
	void simple_count(int&, Node<T> *) const;
	void simple_countEvens(int&, Node<T> *) const;
	int simple_height(Node<T> *) const;
	void simple_leaves(int &, Node<T> *) const;
	void simple_leaf_max(int &, Node<T> *) const;
	int simple_not_leaf(Node<T> *) const;
public:
	BTree();
	BTree<T>& add(const T& data, const char *trace);
	void simplePrint() const;
	//void dottyPrint (ostream&);
	//bool isEmpty();
	bool member(const T&) const;
	void map(mapFn<T>);
	int count() const;
	int countEvens() const;
	int height() const;
	int numberLeaves() const;
	int maxLeaf() const;
	int not_leaf() const;
	~BTree();
};

template<class T>
int BTree<T>::simple_not_leaf(Node<T> *subTreeRoot) const{
	if (subTreeRoot == nullptr){
		return 0;
	}
	if (subTreeRoot->left != nullptr || subTreeRoot->right != nullptr){
		return 1 + simple_not_leaf(subTreeRoot->left) + simple_not_leaf(subTreeRoot->right);
	}
	if (subTreeRoot->left == nullptr && subTreeRoot->right == nullptr){
		return 0;
	}
}

template<class T>
int BTree<T>::not_leaf() const{
	return simple_not_leaf(root);
}

template<class T>
void BTree<T>::simple_leaf_max(int &leaf, Node<T> *subTreeRoot) const{
	if (subTreeRoot == nullptr){
		return;
	}
	if (subTreeRoot->data > leaf){
		leaf = subTreeRoot->data;
	}
	simple_leaf_max(leaf, subTreeRoot->left);
	simple_leaf_max(leaf, subTreeRoot->right);
}

template<class T>
int BTree<T>::maxLeaf() const{
	int max = 0;
	simple_leaf_max(max, root);
	return max;
}

template<class T>
void BTree<T>::simple_leaves(int &leaves, Node<T> *subTreeRoot) const{
	if (subTreeRoot == nullptr){
		return;
	}
	if (subTreeRoot->left == nullptr && subTreeRoot->right == nullptr)
	{
		leaves++;
	}
	simple_leaves(leaves, subTreeRoot->left);
	simple_leaves(leaves, subTreeRoot->right);
}

template<class T>
int BTree<T>::numberLeaves() const{
	int leaves = 0;
	simple_leaves(leaves, root);
	return leaves;
}

template<class T>
void BTree<T>::simple_count(int& count, Node<T> *subTreeRoot) const{
	if (subTreeRoot == nullptr){
		return;
	}
	count++;
	simple_count(count, subTreeRoot->left);
	simple_count(count, subTreeRoot->right);
}

template<class T>
int BTree<T>::simple_height(Node<T> *subTreeRoot) const{
	if (subTreeRoot == nullptr){
		return 0;
	}
	return 1 + max(simple_height(subTreeRoot->left), simple_height(subTreeRoot->right));
}

template<class T>
int BTree<T>::height() const{
	return simple_height(root);
}

template<class T>
int BTree<T>::count() const{
	int count = 0;
	simple_count(count, root);
	return count;
}

template<class T>
void BTree<T>::simple_countEvens(int& count, Node<T> *subTreeRoot) const{
	if (subTreeRoot == nullptr){
		return;
	}
	if (subTreeRoot->data % 2 == 0){
		count++;
	}
	simple_countEvens(count, subTreeRoot->left);
	simple_countEvens(count, subTreeRoot->right);
}

template<class T>
int BTree<T>::countEvens() const{
	int count = 0;
	simple_countEvens(count, root);
	return count;
}

template<class T>
void BTree<T>::map(mapFn<T> f, Node<T> *subTreeRoot)
{
	if (subTreeRoot == NULL)
		return;
	subTreeRoot->data = f(subTreeRoot->data);
	map(f, subTreeRoot->left);
	map(f, subTreeRoot->right);
}

template<class T>
void BTree<T>::map(mapFn<T>f)
{
	map(f, root);
}


template<class T>
bool BTree<T>::member(const T& x) const
{
	return member(x, root);
}


template<class T>
bool BTree<T>::member(const T& x, Node<T> *subTreeRoot) const
{
	if (subTreeRoot == NULL)
		return false;
	return subTreeRoot->data == x ||
		member(x, subTreeRoot->left) ||
		member(x, subTreeRoot->right);
}


template<class T>
void BTree<T>::deleteAll(Node<T> *subTreeRoot)
{
	if (subTreeRoot == NULL)
		return;
	deleteAll(subTreeRoot->left);
	deleteAll(subTreeRoot->right);
	delete subTreeRoot;
}

template <class T>
BTree<T>::~BTree()
{
	deleteAll(root);

}


template <class T>
BTree<T>& BTree<T>::add(const T& x, const char *trace)
{
	add(x, trace, root);
	return *this;
}


template <class T>
bool BTree<T>::add(const T& x, const char *trace, Node<T>* &subTreeRoot)
{
	if (subTreeRoot == NULL)
	{
		assert(strlen(trace) == 0);
		subTreeRoot = new Node<T>(x, NULL, NULL);
		return true;
	}

	assert(strlen(trace)>0);

	if (trace[0] == 'L')
		return add(x, trace + 1, subTreeRoot->left);

	assert(trace[0] == 'R');
	return add(x, trace + 1, subTreeRoot->right);

	return true;

}

template <class T>
BTree<T>::BTree() :root(NULL){}

template <class T>
void BTree<T>::simplePrint() const
{
	simplePrint(root);
	cout << endl;
}

template <class T>
void BTree<T>::simplePrint(Node<T> *subTreeRoot) const
{
	if (subTreeRoot == NULL)
		return;

	cout << subTreeRoot->data << " ";
	simplePrint(subTreeRoot->left);
	simplePrint(subTreeRoot->right);
}

void testMember()
{
	BTree<int> t;

	t.add(10, "").add(12, "L").add(14, "R").add(15, "LR");

	assert(t.member(12) == true);
	assert(t.member(18) == false);
	assert(t.member(15) == true);
}


int plusOne(const int& i)
{
	return i + 1;
}

int main()
{

	testMember();

	BTree<int> t;

	t.add(10, "").add(12, "L").add(14, "R").add(15, "LR").add(16, "LRR");
	t.simplePrint();

	t.map(plusOne);

	t.simplePrint();

	cout << t.count() << endl;
	cout << t.countEvens() << endl;
	cout << t.height() << endl;
	cout << t.numberLeaves() << endl;
	cout << t.maxLeaf() << endl;
	cout << t.not_leaf() << endl;
	return 0;
}