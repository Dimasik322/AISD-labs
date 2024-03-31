#include <map/map.h>
#include <iostream>

using namespace std;

int main() {
	Map<int, int> map;
	map.insert(1, 1);
	map.insert(21, 2);
	map.insert(3, 3);
	map.insert(6, 4);
	map.insert_or_assign(31, 5);
	map.insert_or_assign(1, 6);
	map.print();
	cout << map.erase(61) << endl;
	map.print();
	return 0;
	
}