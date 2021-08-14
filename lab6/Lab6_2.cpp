#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
using namespace std;
template <class T>
class Heap{
protected:
    T *elements;
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
        delete []elements;
    }
    void push(T item);
    void printHeap()
    {
        cout << "Max Heap [ ";
        for (int i = 0; i < count; i++)
            cout << elements[i] << " ";
        cout << "]";
    }
    
private:
    void ensureCapacity(int minCapacity); 
    void reheapUp(int position);
};
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
int main(){
    Heap<int> maxHeap;
for(int i = 0; i <5;i++)
    maxHeap.push(i);
maxHeap.printHeap();
}