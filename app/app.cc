//#include <vector/vector.h>
#include <sort/sort.h>
#include <iostream>

int main() {
	srand(unsigned(time(0)));
	stats stat;
	//compare_sort_random<int>(1000);
	auto array = random_array<string>(10);
	cout << array;	
	stat += merge_sort(array);
	//cout << array;
	return 0;
}