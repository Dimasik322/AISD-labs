//#include <vector/vector.h>
#include <sort/sort.h>
#include <iostream>

int main() {
	srand(unsigned(time(0)));
	auto array = random_array<int>(10);
	cout << array;
	auto stat_shell = bubble_sort(array.begin(), array.end());
	cout << array;
	//cout << stat_bubble;
	//compare_sort_sorted<int>(10000, true);
	return 0;
}