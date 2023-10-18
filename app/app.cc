#include <vector/vector.h>

#include <iostream>

int main() {
	srand(unsigned(time(0)));
	float list1[]{ 1, 0 };
	auto v1 = Vector<float>(list1, 2);
	float list2[]{ 0, 1 };
	auto v2 = Vector<float>(list2, 2);
	cout << bis(v1, v2);
	cout << v1 / 5 << endl;
	cout << v1 * 5 << endl;
	cout <<  5.1f * v1 << endl;
	cout << v1[1];
	return 0;

}