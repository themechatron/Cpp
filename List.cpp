#include<iostream>
template<typename T>
struct Box{
	T data;
	Box* next;
	Box(T _data, Box* _next) : data(_data), next(_next){ }
};
template<typename T>
class List{
private:
	Box<T>* head;
	int count;
public:
	List() :head(nullptr), count(0) { }
	List(T newT){
		head = new Box<T>(newT, nullptr);
		count = 1;
	}
	~List(){
		while (!isEmpty()){
			removeFromHead();
		}
	}
	void insertAtHead(T newT){
		Box<T>* newHead = new Box<T>(newT, head);
		head = newHead;
		count++;
	}
	void removeFromHead(){
		if (head == nullptr){
			return;
		}
		Box<T> *temp = head->next;
		delete head;
		head = temp;
		count--;
	}
	bool isEmpty()const{
		return (head == nullptr);
	}
	void printFoward() const {
		Box<T> *copyHead = head;
		while (copyHead != nullptr){
			std::cout << copyHead->data << " ";
			copyHead = copyHead->next;
		}
		std::cout << std::endl;
	}
	void printBackward() const{
		//still in process
	}
	int size() const{
		int counter = 0;
		Box<T> *copyHead = head;
		while (copyHead != nullptr){
			counter++;
			copyHead = copyHead->next;
		}
		return counter;
	}
};
int main(){
	List<int> zaki(5);
	zaki.insertAtHead(6);
	zaki.printFoward();
	zaki.printFoward();
	zaki.printFoward();
	std::cout << zaki.size();
	system("pause");
	return 0;
}