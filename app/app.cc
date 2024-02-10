#include <set/set.h>
#include <iostream>

int main() {
	//compare(1000);
	vector vec = { 1, 2, 3, 4, 5, 6, 1, 7, 8, 9, 0, 1, 5, 5, 8};
	vector<int> unique = get_unique(vec);
	for (int i(0); i < unique.size(); ++i) {
		cout << unique[i] << " ";
	}
}