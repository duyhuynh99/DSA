#include <iostream>
#include <sstream>
#include <string>
#include <assert.h>

using namespace std;

template <class T>
class SLinkedList {
public:
    class Node; // Forward declaration
protected:
    Node* head;
    Node* tail;
    int count;
public:
    SLinkedList(): head(NULL), tail(NULL), count(0) {};
    ~SLinkedList() { this->clear(); };
    void    add(const T& e);
    void    add(int index, const T& e);
    int     size();
    bool    empty();
    void    clear();
    T       get(int index);
    void    set(int index, const T& e);
    int     indexOf(const T& item);
    bool    contains(const T& item);
    T       removeAt(int index);
    bool    removeItem(const T &removeItem);
    string  toString() {
        stringstream ss;
        ss << "[";
        Node* ptr = head;
        while(ptr != tail){
            ss << ptr->data << ",";
            ptr = ptr->next;
        }
        
        if(count > 0)
            ss << ptr->data << "]";
        else 
            ss << "]";
        return ss.str();
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
        Node(Node* next) {
            this->next = next;
        }
        Node(T data, Node* next = NULL) {
            this->data = data;
            this->next = next;
        }
    };
};

template <class T>
void SLinkedList<T>::add(const T& e) {
    Node* NodeNew = new Node(e);
    if (count == 0) {
        this->head = NodeNew;
        this->tail = NodeNew;
    } else {
        this->tail->next = NodeNew;
        this->tail = NodeNew;
    }
    this->count++;
}

template<class T>
void SLinkedList<T>::add(int index, const T& e) {
    if (index < 0 || index > this->count) {
        throw std::out_of_range("Index is out of range");
    }
    Node* Nodeprev;
    Node* NodeNew = new Node(e);
    if (index == count) {
        return this->add(e);
    } else if (index == 0) {
        NodeNew->next = this->head;
        this->head = NodeNew;
    } else {
        Nodeprev = this->head;
        for (int i = 0; i < index - 1; i++) {
            Nodeprev = Nodeprev->next;
        }
        Node* tempNode = Nodeprev->next;
        Nodeprev->next = NodeNew;
        NodeNew->next = tempNode;
    }
    this->count++;
}

template<class T>
int SLinkedList<T>::size() {
    return this->count;
}
///////////////////////////////////////////////////////
template<class T>
T SLinkedList<T>::get(int index) {
    /* Give the data of the element at given index in the list. */
    if (index < 0 || index >= this->count) {
        throw std::out_of_range("Index is out of range");
    }
    Node* preNode = this->head;
    for (int i = 0; i < index; i++) {
        preNode = preNode->next;
    }
    return preNode->data;
}

template <class T>
void SLinkedList<T>::set(int index, const T& e) {
    /* Assign new value for element at given index in the list */
    if (index < 0 || index >= this->count) {
        throw std::out_of_range("Index is out of range");
    }
    Node* preNode = this->head;
    for (int i = 0; i < index; i++) {
        preNode = preNode->next;
    }
    preNode->data = e;
}

template<class T>
bool SLinkedList<T>::empty() {
    /* Check if the list is empty or not. */
    return (this->count == 0);
}

template<class T>
int SLinkedList<T>::indexOf(const T& item) {
    /* Return the first index wheter item appears in list, otherwise return -1 */
    Node* preNode = this->head;
    for (int i = 0; i < this->count; i++) {
        if (preNode->data == item) {
            return i;
        }
        preNode = preNode->next;
    }
    return -1;
}

template<class T>
bool SLinkedList<T>::contains(const T& item) {
    return (this->indexOf(item) != -1);
}

/////////////////////////////////////////////////////

template <class T>
T SLinkedList<T>::removeAt(int index)
{
    /* Remove element at index and return removed value */
    if (index < 0 || index >= this->count) {
        throw std::out_of_range("Index is out of range");
    }
    Node* preNode = this->head;
    for (int i = 0; i < index - 1; i++) {
        preNode = preNode->next;
    }
    Node* tempNode = preNode->next;
    if (index == 0) {
        this->head = tempNode;
        tempNode = preNode;
    } else {
        preNode->next = tempNode->next;
    }
    if (index == count - 1) {
        this->tail = preNode;
    }
    T temp = tempNode->data;
    delete tempNode;
    this->count--;
    return temp;
}

template <class T>
bool SLinkedList<T>::removeItem(const T& item)
{
    /* Remove the first apperance of item in list and return true, otherwise return false */
    Node* preNode = this->head;
    for (int i = 0; i < this->count; i++) {
        if (preNode->data == item) {
            this->removeAt(i);
            return true;
        }
        preNode = preNode->next;
    }
    return false;
}

template<class T>
void SLinkedList<T>::clear(){
    /* Remove all elements in list */
    	Node *temp;
	while (this->head != NULL) {
		temp = this->head;
		this->head = this->head->next;
		delete temp;
	}
    this->tail = NULL;
	this->count = 0;
}

int main() {
    // SLinkedList<int> list;

    // for (int i = 0; i < 10; ++i) {
    //     list.add(i);
    // }
    // // list.removeAt(0);
    // // list.removeItem(9);



    // list.clear();

    // cout << list.toString();
    // return 0;
    // SLinkedList<int> list;
    // int size = 10;

    // for(int index = 0; index < size; index++){
    // list.add(index);
    // }

    // cout << list.toString();
    // SLinkedList<int> list;

    // for (int i = 0; i < 10; ++i) {
    //     list.add(i);
    // }
    // assert(list.get(0) == list.removeAt(0));

    // cout << list.toString();
    SLinkedList<int> list;

    for (int i = 0; i < 10; ++i) {
        list.add(i);
    }
    assert(list.get(5) == list.removeAt(5));
    list.removeItem(0);
    cout << list.toString();
}