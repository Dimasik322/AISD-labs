#include <vector/vector.h>

#include <iostream>

int main() {
	LinkedList<int> list1;
	list1.push_tail(1);
	list1.push_tail(2);
	list1.push_tail(3);
	cout << list1;

	return 0;
}