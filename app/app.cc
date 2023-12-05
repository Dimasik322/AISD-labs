//#include <vector/vector.h>
#include <sort/sort.h>
#include <iostream>

int main() {
	srand(unsigned(time(0)));
	stats stat;
	compare_sort_sorted<int>(10000, true);
	//auto array = random_array<float>(10);
	//cout << array;	
	//stat += merge_sort(array);
	//cout << array;
	return 0;
}