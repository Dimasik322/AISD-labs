#include <set/set.h>
#include <iostream>

int main() {
	auto set1 = my_set();
	set1.insert(5);
	set1.insert(2);
	set1.insert(7);
	set1.insert(9);
	set1.insert(11);
	set1.insert(13);
	set1.insert(7);
	set1.insert(7);

	set1.print();
}