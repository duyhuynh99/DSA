#include<iostream>
#include<string>
#include<sstream>
using namespace std;

template <class T>
class DLinkedList {
public:
    class Node; // Forward declaration
    class Iterator ;
protected:
    Node* head;
    Node* tail;
    int count;
public:
    DLinkedList() : head(NULL), tail(NULL), count(0){};
    ~DLinkedList(){};
    void    add(const T &e);
    void    add(int index, const T &e);
    int     size();
    bool    empty();
    T       get(int index);
    void    set(int index, const T &e);
    int     indexOf(const T &item);
    bool    contains(const T &item);
    T       removeAt(int index);
    bool    removeItem(const T &item);
    void    clear();
    Iterator begin()
    {
        return Iterator(this, true);
    }
    Iterator end()
    {
        return Iterator(this, false);
    }
public:
    class Node
    {
    private:
        T data;
        Node *next;
        Node *previous;
        friend class DLinkedList<T>;       
        Iterator begin()
        {
            return Iterator(this, true);
        }
        Iterator end()
        {
            return Iterator(this, false);
        }

    public:
        Node()
        {
            this->previous = NULL;
            this->next = NULL;
        }

        Node(const T &data)
        {
            this->data = data;
            this->previous = NULL;
            this->next = NULL;
        }
    }; 
    class Iterator
    {
    private:
        DLinkedList<T> *pList;
        Node *current;
        int index; // is the index of current in pList
    public:
        Iterator(DLinkedList<T> *pList, bool begin);
        Iterator &operator=(const Iterator &iterator);
        void set(const T &e);
        T &operator*();
        bool operator!=(const Iterator &iterator);
        void remove();
        
        // Prefix ++ overload
        Iterator &operator++();
        
        // Postfix ++ overload
        Iterator operator++(int);
    };    
    string toString()
    {
        stringstream ss;
        ss << "[";
        Node *ptr = head;
        while (ptr != tail)
        {
            ss << ptr->data << ",";
            ptr = ptr->next;
        }
        if (count > 0)
            ss << ptr->data << "]";
        else
            ss << "]";
        return ss.str();
    }
};
template <class T>
void DLinkedList<T>::add(const T& e) {
    	Node* newnode = new Node(e);
	if (this->count == 0) {
		this->head= newnode;
        this->tail= newnode;
	}
	else {
		newnode->previous = this->tail;
		this->tail = this->tail->next = newnode;
	}
	this->count++;
}
template<class T>
void DLinkedList<T>::add(int index, const T& e) {
	if (this->count == 0 || index > this->count){
        add(e); 
        return; }
	else {
		if (index == 0) {
			Node* newnode = new Node(e);
			newnode->next = this->head;
			this->head->previous = newnode;
			this->head = newnode;
		}
		else {
			Node* p = this->head;
			for (int i = 0; i < index - 1; i++) {
				p = p->next;
			}
			Node* newnode = new Node(e);
			newnode->next = p->next;
			newnode->previous = p;
			p->next = p->next->previous = newnode;
		}
		this->count++;
	}
}
template<class T>
int DLinkedList<T>::size() {
	return this->count;
}
////////////////////////////////////////////////////////////////////////////
template<class T>
T DLinkedList<T>::get(int index) {
    /* Give the data of the element at given index in the list. */
    Node * Tempnode =this-> head;
            while (index > 0 && Tempnode) {
                Tempnode = Tempnode->next;
                index--;
            }
    return Tempnode->data;
}
template <class T>
void DLinkedList<T>::set(int index, const T& e) {
    /* Assign new value for element at given index in the list */
    if (index >= 0 || index < count) {
            Node * Tempnode = head;
            while (index > 0) {
                Tempnode = Tempnode->next;
                index--;
            }
            Tempnode->data = e;
        }
}
template<class T>
bool DLinkedList<T>::empty() {
    /* Check if the list is empty or not. */
    return this->count == 0;
}
template<class T>
int DLinkedList<T>::indexOf(const T& item) {
    /* Return the first index wheter item appears in list, otherwise return -1 */
    Node * Tempnode =this-> head;
for (int i = 0; i < this->count; i++) {
        if (Tempnode->data == item) {
            return i;
        }
        Tempnode = Tempnode->next;
    }
    return -1;
}
template<class T>
bool DLinkedList<T>::contains(const T& item) {
    /* Check if item appears in the list */
    return (this->indexOf(item) != -1);
}
////////////////////////////////////////////////////////////////////////
template <class T>
T DLinkedList<T>::removeAt(int index)
{
    /* Remove element at index and return removed value */
   if (index < 0 || index >= this->count) {
        throw std::out_of_range("Out of indexx");
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
bool DLinkedList<T>::removeItem(const T &item)
{
    /* Remove the first apperance of item in list and return true, otherwise return false */
    if (!contains(item) || !head)
        return false;
    removeAt(indexOf(item));
    return true;
}
template <class T>
void DLinkedList<T>::clear()
{
    Node *Tempnode;
    while (this->head != NULL)
    {
        Tempnode = this->head;
		this->head = this->head->next;
        delete Tempnode;
    }
    head = NULL;
    tail = NULL;
    count = 0;
}
/////////////////Iterator////////////////////////////////////////////////////////////////////////
template <class T>
DLinkedList<T>::Iterator::Iterator(DLinkedList<T> *pList, bool begin)
{
    this->pList = pList;
    if (begin)
    {
        current = pList->head;
    }
    else
    {
        current = NULL;
    }
}
template <class T>
typename DLinkedList<T>::Iterator &DLinkedList<T>::Iterator::operator=(const DLinkedList<T>::Iterator &iterator)
{
    this->pList = iterator.pList;
    this->current = iterator.current;
    return *this;
}
template <class T>
void DLinkedList<T>::Iterator::set(const T &e)
{
    current->data = e;
}
template <class T>
T &DLinkedList<T>::Iterator::operator*()
{
    return current->data;
}
template <class T>
void DLinkedList<T>::Iterator::remove()
{
    int k = pList->indexOf(current->data);
    if(k != 0) current = current->previous;
    else current = pList->head;
    pList->removeAt(k);
}
template <class T>
bool DLinkedList<T>::Iterator::operator!=(const DLinkedList::Iterator &iterator)
{
    return current != iterator.current;
}
template <class T>
typename DLinkedList<T>::Iterator &DLinkedList<T>::Iterator::operator++()
{
    current = current->next;
    return *this;
}
template <class T>
typename DLinkedList<T>::Iterator DLinkedList<T>::Iterator::operator++(int)
{
    Iterator p = *this;
    current = current->next;
    return p;
}
int main(){
    DLinkedList<int> list;
int size = 10;
for(int idx=0; idx < size; idx++){
    list.add(idx);
}
DLinkedList<int>::Iterator it = list.begin();
for(; it != list.end(); it++)
{
    cout << *it << " |";
}
}