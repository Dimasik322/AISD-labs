#include <vector/vector.h>

#include <iostream>

int main() {
	srand(unsigned(time(0)));

	/*auto list1 = LinkedList<Coef<int>>();
	list1.push_tail(Coef<int>(1, 2));
	list1.push_tail(Coef<int>(2, 4));
	list1.push_tail(Coef<int>(1, 5));
	list1.push_head(Coef<int>(6, 8));
	list1.push_head(Coef<int>(0, 2));
	list1.push_tail(Coef<int>(0, 2)); 
	auto list2 = list1;
	auto list3 = LinkedList<Coef<int>>(list2);
	auto list4 = LinkedList<Coef<int>>();
	list4.push_tail(Coef<int>(3, 1));
	list4.push_tail(Coef<int>(1, 6));
	list3.push_tail(list4);
	cout << list3 << endl;
	list3.pop_head();
	list3.pop_tail();
	list3.delete_node(Coef<int>(1, 2));
	cout << list3 << endl;
	cout << list3[2] << endl;
	cout << list1.get_value(2) << endl;
	auto list_random = LinkedList<Coef<int>>(4, 10, 5);
	cout << list_random << endl;*/


	/*auto list1 = LinkedList<Coef<int>>();
	list1.push_tail(Coef<int>(1, 2));
	list1.push_tail(Coef<int>(2, 4));
	list1.push_tail(Coef<int>(1, 5));
	list1.push_tail(Coef<int>(0, 2));
	list1[0] = Coef<int>(0, 2);
	cout << list1;*/

	//проверка функций обычного списка
	/*auto list1 = LinkedList<int>();
	list1.push_head(1);
	list1.push_head(3);
	list1.push_head(4);
	list1.push_head(5);
	list1.push_head(4);
	list1.pop_tail();
	list1.delete_node(4);
	auto list2 = LinkedList<int>();
	list2.push_tail(2);
	list2.push_tail(9);
	list2.push_head(list1);
	cout << list2 << endl;
	auto list3 = LinkedList<int>(list2);
	cout << list3 << endl;
	cout << list3[1] << endl;
	list3 = list1;
	cout << list3 << endl;
	auto list_random = LinkedList<int>(4, 10);
	cout << list_random << endl;*/


	return 0;
}