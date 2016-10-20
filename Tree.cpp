#include<iostream>
#include<ostream>
#include<string>

using namespace std;
struct Node{
	int data;
	Node* left, *right;
	Node(int d, Node *l=nullptr, Node *r=nullptr) :data(d), left(l), right(r){};
};
class Tree{
private:
	//typedef const string& position_t; 
	//defining type 
	using position_t = const string&;
	Node* root;
	size_t size;
	void freeNode(Node *ptr){
		if (ptr == nullptr)
			return;
		freeNode(ptr->left);
		freeNode(ptr->right);
		delete ptr;
	}
	bool isValidPath(position_t path){
		for (size_t i = 0; i < path.size(); i++){
			if (path[i] != 'l' && path[i] != 'r' && path[i] != ' '){
				return false;
			}
		}
		return true;
	}
	/*Node* navigate(position_t position){
		Node* ptr = root;
		for (size_t i = 0; i < position.size(); i++){
			if (position[i] == 'l') ptr = ptr->left;
			else if (position[i] == 'r') ptr = ptr->right;
		}
		return ptr;
	}*/
	Node** navigate(position_t position){
		if (!isValidPath(position)){
			return nullptr;
		}
		Node** to_remove = &root;
		for (size_t i = 0; i < position.size(); i++){
			if (position[i] == 'l') to_remove = &((*to_remove)->left);
			else if (position[i] == 'r') to_remove = &((*to_remove)->right);
		}
		return to_remove;
	}
public:
	Tree() :root(nullptr), size(0){};
	Tree(const Tree&) = delete; //to-do later
	Tree& operator = (const Tree&) = delete; //to-do later
	void insert(int x, position_t position){
		Node **to_insert = navigate(position);
		if (to_insert != nullptr) {
			*to_insert = new Node(x);
		}
	}
	void remove(position_t position){
		//Node* to_remove = navigate(position);
		//string parentPos = position;
		//if (!parentPos.empty())
		//{
		//	parentPos.pop_back(); //removes the last symbol
		//	Node* parent = navigate(parentPos);
		//	if (position.back() == 'l'){
		//		parent->left = nullptr;
		//	}
		//	else{
		//		parent->right = nullptr;
		//	}
		//}
		//else{
		//	root = nullptr;
		//}
		//freeNode(to_remove);
		Node **to_remove = navigate(position);
		if (to_remove != nullptr){
			freeNode(*to_remove);
			*to_remove = nullptr;
		}
	}
	static void printNode(ostream& os, Node* ptr){
		if (ptr == nullptr)
			return;
		os << ptr->data << " ->";
		if (ptr->left == nullptr) os << "#";
		else os << ptr->left->data;
		os << ", ";
		if (ptr->right == nullptr) os << "#";
		else os << ptr->right->data;
		os << "\n";
		printNode(os, ptr->left);
		printNode(os, ptr->right);
	}
	friend ostream& operator<<(ostream& os, const Tree& t){
		printNode(os, t.root);
		return os;
	}
	~Tree(){
		freeNode(root);
	}
};

int main(){
	Tree t;
	t.insert(1, "");
	t.insert(2, "l");
	t.insert(3, "r");
	t.insert(5, "ll");
	cout << t;
	system("pause");
	return 0;
}
/*
void specialInsert(int x){
	insert(x,calculatePosition);
}

*/