#include <vector/vector.h>

#include <iostream>
#include <complex> 

int main() {
	srand(unsigned(time(0)));
	float list1[]{ 1, 0 };
	float list2[]{ 0, 1 };
	int list3[]{ 0, 1 };
	float list4[]{ 4.0f, 4.0f };
	float list5[]{ 7.0f, 3.0f };
	auto v1 = Vector(list1, 2);
	auto v2 = Vector(list2, 2);
	auto v3 = Vector(list3, 2);
	auto v4 = Vector(list4, 2);
	auto v5 = Vector(list5, 2);
	cout << bis(v1, v2)<< endl;
	//auto v3 = Vector<int>();
	//cout << v3;
	//complex<int> list[]{complex(3, 1), complex(1, 2)};
	//complex<int> lsit[]{complex(2, 1), complex(0, 1) };
	//auto v1 = Vector<complex<int>>(list, 2);
	//auto v2 = Vector<complex<int>>(lsit, 2);
	//cout << v1 << endl;
	//cout << v2 << endl;
	//v1 *= 3;
	//cout << v1.abs();
	//auto v4 = Vector<float>(v3);
	//cout << v4.abs();
	//cout << v3.get_size() << " items:" << endl;;
	//for (int i(0); i < v1.get_size(); i++) {
		//cout << v1[i] << endl;
	//}
	//v1 = v1 + v2;
	//for (int i(0); i < v1.get_size(); i++) {
	//	cout << v1[i] << endl;
	//}
	//cout << "scalar value = " << v1 * v2 << endl;
	//cout << 1 << endl;
	//cout << cos(v1, v2);
	//auto v3 = bis(v1, v2);
	//cout << v3.get_size() << endl;
	//cout << v3[0] << v3[1];
	//cout << v1;
	//bool b = v1 == v2;
	//cout << b;
	return 0;

}