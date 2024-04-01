#include <map/map.h>
#include <iostream>
#include <unordered_map>

using namespace std;

int main() {
	//auto hash_10 = Hash<int>(10);

	Map<int, string, Hash<int>> map;
	map.insert(1, "werfe");
	map.insert(21, "efewe");
	map.insert(3, "wafe");
	map.insert(6, "efwe");
	map.insert_or_assign(31, "egsgs");
	map.insert_or_assign(1, "esgew");
	map.print();
	cout << map.erase(61) << endl;
	map.print();
	cout << endl;

	//unordered_map<

	return 0;
	
}