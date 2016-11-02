#include<iostream>
#include<vector>
using namespace std;

template<class T>
struct Node{
	T data;
	Node<T>* left;
	Node<T>* right;
	Node(T _data, Node<T>* _left, Node<T>* _right) : data(_data), left(_left), right(_right){ };
};
template<class T>
class BSTree{
private:
	Node<T>* root;
	bool containsRec(const T&, Node<T>*)const;
	Node<T>*& find(const T&,Node<T>*);
	void inorder(Node<T>*, vector<T>&) const;
	void preorder(Node<T>*, vector<T>&) const;
	void postorder(Node<T>*, vector<T>&) const;
public:
	BSTree();
	~BSTree();
	BSTree(const BSTree&);
	BSTree<T>& operator=(const BSTree&);
	void add(const T&);
	void remove(const T&);
	bool contains(const T&) const;
	vector<T> inorderTraversal() const;
	vector<T> preorderTraversal() const;
	vector<T> postorderTraversal() const;
};
template<class T>
BSTree<T>::BSTree() :root(nullptr);

template<class T>
bool BSTree<T>::containsRec(const T& val, Node<T>* subRoot) const{
	if (subRoot == nullptr){
		return false;
	}
	if (T == subRoot->data){
		return true;
	}
	else if (val > subRoot->data){
		return containsRec(val, subRoot->right);
	}
	else{
		return constainRec(cal, subRoot->left);
	}
}

template<class T>
bool BSTree<T>::contains(const T& val) const{
	return containsRec(val, root);
}

template<class T>
Node<T>*& BSTree<T>::find(const T& el,Node<T>* subRoot){
	if (node == nullptr || node->data == el){
		return subRoot;
	}
	if (el < subRoot->left){
		return find(el, subRoot->left);
	}
	else{
		return find(el, subRoot->right);
	}
}

template<class T>
void BSTree<T>::add(const T& el){
	Node<T>*& found = find(el, root);
	if (found == nullptr){
		found = new Node<T>(el);
	}
}

template<class T>
void BSTree<T>::remove(const T& el){
		Node<T>* to_remove = find(el, root);
	if (to_remove == nullptr){
		return;
	}
	if (to_remove->left == nullptr){
		Node<T>* temp = to_remove;
		to_remove = to_remove->right;
		delete temp;
	}
	else{
		Node<T>* rightmost = to_remove->left;
		while (rightmost->right != nullptr){
			rightmost = rightmost->right;
		}
		rightmost->right = to_remove->right;
		Node<T>* temp = to_remove;
		to_remove = to_remove->left;
		delete temp;
	}
}

template<class T>
void BSTree<T>::inorder(Node<T>* node, vector<T>& result)const{
	if (node == nullptr){
		return;
	}
	inorder(node->left, result);
	result.push_back(node->data);
	inorder(node->right, result);
}

template<class T>
vector<T> BSTree<T>::inorderTraversal() const{
	vector<T> result;
	inorder(root, result);
	return result;
}

template<class T>
void BSTree<T>::preorder(Node<T>* node, vector<T>& result)const{
	if (node == nullptr){
		return;
	}
	result.push_back(node->data);
	preorder(node->left, result);
	preorder(node->right, result);
}

template<class T>
vector<T> BSTree<T>::preorderTraversal() const{
	vecor<T> result;
	preorder(root, result);
	return result;
}

template<class T>
void BSTree<T>::postorder(Node<T>* node, vector<T>& result)const{
	if (node == nullptr){
		return;
	}
	postorder(node->left, result);
	postorder(node->right, result);
	result.push_back(node->data);
}

template<class T>
vector<T> BSTree<T>::postorderTraversal() const{
	vecor<T> result;
	postorder(root, result);
	return result;
}
int main(){

	system("pause");
	return 0;
}