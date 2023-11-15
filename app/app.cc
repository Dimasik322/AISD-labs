#include <vector/vector.h>

#include <iostream>

int main() {
	srand(unsigned(time(0)));
	LinkedList<int> list1;
	list1.push_head(1);
	list1.push_head(2);
	list1.push_head(3);
	list1.push_tail(2);
	list1.push_tail(1);
	list1.push_tail(1);
	list1.push_tail(2);
	cout << list1 << endl;
	cout << list1[1] << endl;
	list1.pop_head();
	list1.pop_tail();
	cout << list1 << endl;


	LinkedList<int> list2;
	list2.push_tail(4);
	list2.push_tail(5);
	list2.push_tail(6);
	list2.push_tail(7);


	list1.push_tail(list2);
	cout << list1 << endl;
	list1.delete_node(2);
	cout << list1 << endl;
	list1[0] = 0;
	cout << list1 << endl;


	auto list = LinkedList<int>(4, 5);
	cout << list << endl;
	print(list);
	cout << endl;
	cout << get_value(list, 3) << endl;

	auto list_copy = LinkedList<int>(list2);
	cout << list_copy << endl;

	list_copy = list1;
	cout << list1 << endl;


	LinkedList<int> list3 = list1 + list2;
	cout << list3 << endl;

	return 0;
}