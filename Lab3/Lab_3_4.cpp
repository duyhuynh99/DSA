#include <iostream>
#include <sstream>
using namespace std;

template <class T>
class SLinkedList {
public:
	class Node; 
protected:
	Node* head;
	Node* tail;
	int count;
public:
	SLinkedList() {
		this->head = nullptr;
		this->tail = nullptr;
		this->count = 0;
	}
	~SLinkedList() {};
	void add(T e) {
		Node *pNew = new Node(e);
		if (this->count == 0) {
			this->head = this->tail = pNew;
		}
		else {
			this->tail->next = pNew;
			this->tail = pNew;
		}

		this->count++;
	}
	int size() {
		return this->count;
	}
	void printList(){
		stringstream ss;
		ss << "[";
		Node *ptr = head;
		while (ptr != tail) {
			ss << ptr->data << ",";
			ptr = ptr->next;
		}
		if (count > 0) {
			ss << ptr->data << "]";
		}
		else {
			ss << "]";
		}
		cout << ss.str() << endl;
	}
public:
	class Node {
	private:
		T data;
		Node* next;
		friend class SLinkedList<T>;
	public:
		Node() {
			next = 0;
		}
		Node(T data) {
			this->data = data;
			this->next = nullptr;
		}
	};

	void bubbleSort();
};

template <class T>
void SLinkedList<T>::bubbleSort() {
	while (this->tail->next != this->head->next) {
		Node* troller = this->head;
		Node* largest = troller;
		while (troller !=  this->tail->next) {
			if (troller->data < largest->data) {
				T temp = troller->data;
				troller->data = largest->data;
				largest->data = temp;
			}
			largest = troller;
			troller = troller->next;
		}
		 this->tail->next = largest;
		printList();
	}
}

int main() {
	int arr[] = { 9, 2, 8, 4, 1 };
	SLinkedList<int> list;
	for (int i = 0; i <int(sizeof(arr)) / 4; i++)
		list.add(arr[i]);
	list.bubbleSort();
	return 0;
}
