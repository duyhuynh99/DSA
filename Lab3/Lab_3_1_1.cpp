#ifndef SORTING_H
#define SORTING_H

#include <sstream>
#include <iostream>
#include <type_traits>
using namespace std;

template <class T>
class Sorting {
private:
	static void printArray(T* start, T* end) {
		int size = end - start;
		for (int i = 0; i < size; i++)
			cout << start[i] << " ";
		cout << endl;
	}
	 static void sortSegment(T* start, T* end, int segment_idx, int cur_segment_total);

public:
	 static void ShellSort(T* start, T* end, int* num_segment_list, int num_phases);
};
#endif


template <class T>
static void sortSegment(T* start, T* end, int segment_idx, int cur_segment_total) {
    int count = (int)(end - start);
    int current = segment_idx + cur_segment_total;
    while (current < count) {
        T temp = *(start + current);
        int walker = current - cur_segment_total;
        while (walker >= 0 && temp < *(start + walker)) {
            *(start + walker + cur_segment_total) = *(start + walker);
            walker -= cur_segment_total;
        }
        *(start + walker + cur_segment_total) = temp;
        current += cur_segment_total;
    }
}
template <class T>
static void ShellSort(T* start, T* end, int* num_segment_list, int num_phases) {
    // TODO
    // Note: You must print out the array after sorting segments to check whether your algorithm is true.
    int *k = num_segment_list + num_phases - 1;
    while ((int)*k >= 1) {
        int segment = 0;
        while (segment < (int)*k) {
            sortSegment(start, end, segment, (int)*k);
            segment++;
        }
        cout << (int)*k << " segments: ";
        printArray(start, end);
        if ((int)*k == 1)
            break;
        k--;
    }
}
int main() {
	int num_segment_list[] = { 1, 3, 5 };
	int num_phases = 3;
	int array[] = { 10, 9, 8 , 7 , 6, 5, 4, 3, 2, 1 };
	Sorting<int>::ShellSort(&array[0], &array[10], &num_segment_list[0], num_phases);
	return 0;
}