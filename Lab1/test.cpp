#include <iostream>
#include <string>
#include <sstream>

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
    ~SLinkedList() { };
    void    add(const T& e);
    void    add(int index, const T& e);
    int     size();
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
int main(){
    SLinkedList<int> list;
int size = 10;

for(int index = 0; index < size; index++){
    list.add(0,index);
}

cout << list.toString();
return 0;
}