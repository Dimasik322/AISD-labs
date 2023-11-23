#pragma once

#include <vector>
#include <iostream>
#include <random>

using namespace std;

class TestClass {
private:
	int value;

public:
	TestClass() :value(0) {};
	TestClass(const int value) :value(value) {};
	bool operator>(const TestClass& rhs) {
		return this->value > rhs.value;
	}
};

struct stats {
	size_t comparison_count = 0;
	size_t copy_count = 0;
};

std::ostream& operator<<(std::ostream& os, stats& stat)
{
	os << "comparison_count = " << stat.comparison_count << " copy_count = " << stat.copy_count << endl;
	return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, vector<T>& array)
{
	for (int i(0); i < array.size(); ++i) {
		os << array[i] << " ";
	}
	os << endl;
	return os;
}

template<typename T>
void swap(std::vector<T>& array, int a, int b) {
	T tmp = array[a];
	array[a] = array[b];
	array[b] = tmp;
}

template<typename T>
stats& bubble_sort(vector<T>& array) {
	stats sort_stats;
	for (int i(0); i < (array.size() - 1); ++i) {
		for (int j(0); j < (array.size() - i - 1); ++j){
			if (array[j] > array[j + 1]) {
				swap(array, j, j + 1);
				sort_stats.copy_count += 3;
			}
			sort_stats.comparison_count += 1;
		}
	}
	return sort_stats;
}

template<typename T>
stats& shell_sort(vector<T>& array) {
	stats sort_stats;
	for (int i(int(array.size())); i > 0; i/=2){
		for (int j(i); j < (array.size()); ++j) {
			for (int k(j - i); (k >= 0) && (array[k] > array[k + i]); k -= i) {
				swap(array, k, k+i);
				sort_stats.copy_count += 3;
			}
		}
	}
	return sort_stats;
}

template<typename T>
vector<T> random_array(const int& len) {
	vector<T> array{};
	for (int i(0); i < len; ++i) {
		array.push_back((T)(rand()));
	}
	return array;
}

template<>
vector<float> random_array<float>(const int& len) {
	vector<float> array{};
	for (int i(0); i < len; ++i) {
		array.push_back((float)rand()/(float)1000);
	}
	return array;
}

template<>
vector<string> random_array<string>(const int& len) {
	vector<string> array{};
	for (int i(0); i < len; ++i) {
		string str{};
		for (int j(0); j < 10; ++j) {
			str += char((int)(rand()) * 26 / RAND_MAX + 97);
		}
		array.push_back(str);
	}
	return array;
}

template<typename T>
vector<T> sorted_array(const int& len, const bool& reverse) {
	vector<T> array{};
	if (reverse == false) {
		for (int i(0); i < len; ++i) {
			array.push_back(i);
		}
	}
	else {
		for (int i(0); i < len; ++i) {
			array.push_back(len - i);
		}
	}
	return array;
}



