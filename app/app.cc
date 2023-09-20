#include <vector/vector.h>

#include <iostream>
#include <complex> 



int main() {
	float list[]{ 1, 4};
	float lsit[]{ 4, 2};
	auto v1 = Vector<float>(list, 2);
	auto v2 = Vector<float>(lsit, 2);
	//auto v3 = Vector<float>(v1);
	/*cout << v3.get_size() << " items:" << endl;;
	for (int i(0); i < v3.get_size(); i++) {
		cout << v3[i] << endl;
	}
	v1 = v1 - v2;
	for (int i(0); i < v1.get_size(); i++) {
		cout << v1[i] << endl;
	}*/
	//cout << "scalar value = " << v1 * v2 << endl;
	//cout << 1 << endl;
	//cout << cos(v1, v2);
	auto v3 = bis(v1, v2);
	cout << v3.get_size() << endl;
	cout << v3[0] << v3[1];

	return 0;

}