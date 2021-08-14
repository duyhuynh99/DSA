#include <iostream>
using namespace std;

template <class T>
class Sorting {
public:
	static void printArray(T *start, T *end) {
		int count = end - start;
		for (int i = 0; i < count - 1; i++) {
			cout << start[i] << ", ";
		}
		cout << start[count - 1];
		cout << endl;
	}

	static void oddEvenSort(T *start, T *end) {
		bool isSorted = false;
		int count = end - start;
		while (!isSorted) {
			isSorted = true;
			int a=0;
			while ( a <= count - 2) {
				if (*(start + a) > *(start + a + 1)) {
					T temp = *(start + a);
					*(start + a) = *(start + a + 1);
					*(start + a + 1) = temp;
					isSorted = false;
					a=a+2;
				}
			}
			int b=1;
			while (b <= count - 2) {
				if (*(start + b) > *(start + b + 1)) {
					T temp = *(start + b);
					*(start + b) = *(start + b + 1);
					*(start + b + 1) = temp;
					isSorted = false;
					b=b+2;
				}
			}
			printArray(start, end);
		}
		return;
	}
};

int main() {
	int arr[] = { 1,2,2 };
	Sorting<int>::oddEvenSort(&arr[0], &arr[3]);
	return 0;
}