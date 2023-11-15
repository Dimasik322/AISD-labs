#include <vector/vector.h>

#include <iostream>

int main() {
	srand(unsigned(time(0)));
	auto list1 = LinkedList<Coef<int>>();
	list1.push_tail(Coef<int>(1, 2));
	list1.push_tail(Coef<int>(4, 3));
	list1.push_tail(Coef<int>(9, 6));
	list1.push_tail(Coef<int>(3, 4));
	LinkedList<Coef<int>> list2;
	list2.push_tail(Coef<int>(7, 5));
	list2.push_head(list1);
	cout << list1 << endl;
	cout << list2 << endl;
	auto list3 = LinkedList<Coef<int>>(4, 5, 9);
	//cout << list1 << endl;
	//cout << list1.get_head()->value.coef;
	//cout << list1.get_head()->next->value.coef;
	//cout << list1.get_head()->next->next->value.coef;
	cout << get_value(list1, 2) << endl;
	cout << list3 << endl;
	return 0;
}