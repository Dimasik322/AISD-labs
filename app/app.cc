#include <vector/vector.h>

#include <iostream>
#include <complex> 



int main() {
	int list[]{ 1, 2};
	int lsit[]{ 1, -1};
	auto v1 = Vector<int>(list, 2);
	auto v2 = Vector<int>(lsit, 2);
	cout << v1.get_size() << " items:" << endl;;
	for (int i(0); i < v1.get_size(); i++) {
		cout << v1[i] << endl;
	}
	//cout << "scalar value = " << scalar(v1, v2) << endl;
	//cout << 1 << endl;

	//cout << cos(v1, v2);
	return 0;
}