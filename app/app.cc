#include <map/map.h>
#include <iostream>

using namespace std;

int main() {
	Map<int, int> map;
	map.insert(1, 123124);
	map.insert(21, 124);
	map.insert(3, 14);
	map.insert(6, 3124);
	map.print();

	return 0;
	
}