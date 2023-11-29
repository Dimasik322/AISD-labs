//#include <vector/vector.h>
#include <sort/sort.h>
#include <iostream>

int main() {
	srand(unsigned(time(0)));
	auto array = random_array<int>(10);
	cout << array;
	auto stat_shell = selection_sort(array);
	//cout << array;
	//cout << stat_bubble;
	//compare_sort_random<int>(1000);
	return 0;
}