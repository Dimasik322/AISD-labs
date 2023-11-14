#include <vector/vector.h>

#include <iostream>

int main() {
	srand(unsigned(time(0)));
	LinkedList<int> list1;
	list1.push_tail(2);
	list1.push_tail(2);
	list1.push_tail(2);
	cout << list1;

	return 0;
}