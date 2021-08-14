#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
using namespace std;
template <class T>
class Heap {
protected:
    T* elements;
    int capacity;
    int count;
public:
    Heap()
    {
        this->capacity = 10;
        this->count = 0;
        this->elements = new T[capacity];
    }
    ~Heap()
    {
        delete[]elements;
    }
    void push(T item);
    int getItem(T item);
    void remove(T item);
    void clear();
    void printHeap()
    {
        cout << "Max Heap [ ";
        for (int i = 0; i < count; i++)
            cout << elements[i] << " ";
        cout << "]\n";
    }
private:
    void ensureCapacity(int minCapacity);
    void reheapUp(int position);
    void reheapDown(int position);
};
// ----------------------------------------------------------------
template<class T>
void Heap<T>::push(T item){
    if(count>=capacity) ensureCapacity(10);
    int lastvariable=count;
    elements[lastvariable]=item;
    count++;
    reheapUp(lastvariable);
}

template<class T>
void Heap<T>::ensureCapacity(int minCapacity){
    this->capacity=this->capacity+minCapacity;
    T *nevergiveup=new T[capacity];
    int a=0;
    while( a<count){
        nevergiveup[a]=elements[a];
        a++;
    }
    this->elements=new T[capacity];
    int b=0;
    while( b<count){
        elements[b]=nevergiveup[b];
        b++;
    }
}

template<class T>
void Heap<T>::reheapUp(int position){
if(count>capacity||position<0||position>count) return;
   if(position>0){
       int parent= (position-1)/2;
       if(elements[position]>elements[parent]){
           std::swap(elements[position],elements[parent]);
           reheapUp(parent);
       }
   } 
}
// --lab6_3------------------------------------------------------------------------------
template<class T>
int Heap<T>::getItem(T item) {
    // TODO: return the index of item in heap
    for (int i = 0; i < this->count; i++) {
        if (this->elements[i] == item) return i;
    }
    return -1;
}

template<class T>
void Heap<T>::remove(T item) {
    // TODO: remove the element with value equal to item
    if(count==0)return;
    for(int i=0;i<count;i++){
    if(i==count&&elements[i]==item)count--;
    else
        if(elements[i]==item){
            elements[i]=elements[count-1];
            count--;
            reheapDown(i);
        }
    }
   
}

template<class T>
void Heap<T>::clear() {
    // TODO: delete all elements in heap
    delete[]elements;
    capacity=10;
    count=0;
    
}
int main(){
    Heap<int> maxHeap;
int arr[] = {42,35,30,15,20,21,18,3,7,14};
for (int i = 0; i < 10; i++)
    maxHeap.push(arr[i]);
maxHeap.remove(42);
maxHeap.remove(35);
maxHeap.remove(30);
maxHeap.printHeap();
}