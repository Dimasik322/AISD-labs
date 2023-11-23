//#include <vector/vector.h>
#include <sort/sort.h>
#include <iostream>

int main() {
	srand(unsigned(time(0)));
	vector<int> array = sorted_array<int>(10000, true);
	//cout << array;
	auto stat_bubble = bubble_sort(array);
	//cout << array;
	cout << stat_bubble;
	return 0;
}