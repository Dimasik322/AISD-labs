#include <set/set.h>
#include <iostream>

int main() {
	auto set1 = my_set();
	set1.insert(13);
	set1.insert(8);
	set1.insert(17);
	set1.insert(15);
	set1.insert(25);
	set1.insert(22);
	set1.insert(27);
	set1.insert(1);
	set1.insert(11);
	set1.insert(6);
	set1.print();

	auto set2 = my_set();
	set2.insert(5);
	set2.insert(2);
	set2.insert(7);
	set2.print();

	set2 = set1;
	set2.print();
}