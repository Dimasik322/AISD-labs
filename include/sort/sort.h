#pragma once

#include <vector>
#include <iostream>
#include <random>
#include <exception>
//#include <iterator>

using namespace std;

class TestClass {
private:
	int value;

public:
	TestClass() :value(0) {};
	TestClass(const int value) :value(value) {};
	int get_value() {
		return this->value;
	}
	bool operator>(const TestClass& rhs) {
		return this->value > rhs.value;
	}
	bool operator<(const TestClass& rhs) {
		return !(*this > rhs);
	}
};

struct stats {
	size_t comparison_count = 0;
	size_t copy_count = 0;
	void operator+=(const stats& rhs) {
		this->comparison_count += rhs.comparison_count;
		this->copy_count += rhs.copy_count;
	}
	void operator/=(const int& value) {
		this->comparison_count /= value;
		this->copy_count /= value;
	}
};

std::ostream& operator<<(std::ostream& os, stats& stat)
{
	os << "comparison_count = " << stat.comparison_count << " copy_count = " << stat.copy_count;
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

std::ostream& operator<<(std::ostream& os, TestClass rhs) {
	os << rhs.get_value();
	return os;
}

template<typename T>
void swap(std::vector<T>& array, int a, int b) {
	T tmp = array[a];
	array[a] = array[b];
	array[b] = tmp;
}

template<typename T>
stats& bubble_sort(vector<T> array) {
	stats sort_stats;
	for (int i(0); i < (array.size() - 1); ++i) {
		sort_stats.comparison_count += 1;
		for (int j(0); j < (array.size() - i - 1); ++j){
			sort_stats.comparison_count += 1;
			if (array[j] > array[j + 1]) {
				swap(array, j, j + 1);
				sort_stats.copy_count += 3;
			}
			sort_stats.comparison_count += 1;
		}
		sort_stats.comparison_count += 1;
	}
	sort_stats.comparison_count += 1;
	return sort_stats;
}

template<class Iterator>
stats& bubble_sort(Iterator begin, Iterator end) {
	stats sort_stats;
	--end;
	for (auto i(begin); i < end; i++) {
		sort_stats.comparison_count += 1;
		for (auto j(begin); j != end; j++) {
			sort_stats.comparison_count += 1;
			if (*j > *(j + 1)) {
				sort_stats.comparison_count += 1;
				swap(*j, *(j + 1));
				sort_stats.copy_count += 3;
			}
		}
		sort_stats.comparison_count += 1;
	}
	sort_stats.comparison_count += 1;
	return sort_stats;
}

template<typename T>
stats& shell_sort(vector<T> array) {
	stats sort_stats;
	for (int i(int(array.size())); i > 0; i /= 2){
		sort_stats.comparison_count += 1;
		for (int j(i); j < (array.size()); ++j) {
			sort_stats.comparison_count += 1;
			for (int k(j - i); (k >= 0) && (array[k] > array[k + i]); k -= i) {
				sort_stats.comparison_count += 1;
				swap(array, k, k+i);
				sort_stats.copy_count += 3;
			}
			sort_stats.comparison_count += 1;
		}
		sort_stats.comparison_count += 1;
	}
	sort_stats.comparison_count += 1;
	return sort_stats;
}

template<typename Iterator>
stats& shell_sort(Iterator begin, Iterator end) {
	stats sort_stats;
	for (auto i = (end - begin) / 2; i != 0; i /= 2) {
		sort_stats.comparison_count += 1;
		for (auto j = begin + i; j != end; ++j) {
			sort_stats.comparison_count += 1;
			for (auto k = j; k - begin >= i && (*k < *(k - i)); k -= i) {
				sort_stats.comparison_count += 1;
				std::swap(*k, *(k - i));
				sort_stats.copy_count += 3;
			}
			sort_stats.comparison_count += 1;
		}
		sort_stats.comparison_count += 1;
	}
	sort_stats.comparison_count += 1;
	return sort_stats;
}

template<typename T>
stats& pyramid_sort(vector<T> array) {

}

template<typename Iterator>
stats& pyramid_sort(Iterator begin, Iterator end) {

}

template<typename T>
vector<T> random_array(const int& len) {
	if (len <= 0) {
		throw length_error("ћассив не может быть отрицательным или нулевым");
	}
	vector<T> array{};
	array.reserve(len);
	//array.resize(len);
	for (int i(0); i < len; ++i) {
		//array[i] = (T)(rand());
		//array.push_back((T)(rand()));
		array.emplace_back((T)(rand()));
	}
	return array;
}

template<>
vector<TestClass> random_array(const int& len) {
	if (len <= 0) {
		throw length_error("ћассив не может быть отрицательным или нулевым");
	}
	vector<TestClass> array{};
	array.reserve(len);
	//array.resize(len);
	for (int i(0); i < len; ++i) {
		//array[i] = (T)(rand());
		//array.push_back((T)(rand()));
		array.emplace_back(TestClass((int)(rand())));
	}
	return array;
}

template<>
vector<float> random_array<float>(const int& len) {
	if (len <= 0) {
		throw length_error("ћассив не может быть отрицательным или нулевым");
	}
	vector<float> array{};
	//array.resize(len);
	array.reserve(len);
	for (int i(0); i < len; ++i) {
		//array[i] = ((float)rand() / (float)1000);
		array.emplace_back((float)rand() / (float)1000);
	}
	return array;
}

template<>
vector<string> random_array<string>(const int& len) {
	if (len <= 0) {
		throw length_error("ћассив не может быть отрицательным или нулевым");
	}
	vector<string> array{};
	//array.resize(len);
	array.reserve(len);
	for (int i(0); i < len; ++i) {
		string str{};
		for (int j(0); j < 10; ++j) {
			str += char((int)(rand()) * 26 / RAND_MAX + 97);
		}
		//array[i] = str;
		array.emplace_back(str);
	}
	return array;
}

template<typename T>
vector<T> sorted_array(const int& len, const bool& reverse) {
	if (len <= 0) {
		throw length_error("ћассив не может быть отрицательным или нулевым");
	}
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

template<>
vector<TestClass> sorted_array(const int& len, const bool& reverse) {
	if (len <= 0) {
		throw length_error("ћассив не может быть отрицательным или нулевым");
	}
	vector<TestClass> array{};
	if (reverse == false) {
		for (int i(0); i < len; ++i) {
			array.push_back(TestClass(i));
		}
	}
	else {
		for (int i(0); i < len; ++i) {
			array.push_back(TestClass(len - i));
		}
	}
	return array;
}

template<typename T>
void compare_sort_random(const int& len) {
	if (len <= 0) {
		throw length_error("ћассив не может быть отрицательным или нулевым");
	}
	cout << len << ":" << endl;
	stats stat_bubble;
	stats stat_shell;
	stats stat_pyramid;
	for (int i(0); i < 100; ++i) {
		vector<T> array = random_array<T>(len);
		stat_bubble += bubble_sort(array);
		stat_shell += shell_sort(array);
		//stat_pyramid += shell_pyramid(array);
	}
	stat_bubble /= 100;
	stat_shell /= 100;
	//stat_pyramid /= 100;
	cout << "bubble : " << stat_bubble << endl;
	cout << "shell : " << stat_shell << endl;
	//cout << "pyramid : " << stat_pyramid << endl;
}

template<typename T>
void compare_sort_sorted(const int& len, const bool& reverse) {
	if (len <= 0) {
		throw length_error("ћассив не может быть отрицательным или нулевым");
	}
	stats stat_bubble;
	stats stat_shell;
	stats stat_pyramid;
	vector<T> array = sorted_array<T>(len, reverse);
	if (reverse == true) {
		cout << len << " reverse sorted:" << endl;
	}
	else {
		cout << len << " sorted:" << endl;
	}
	stat_bubble += bubble_sort(array);
	stat_shell += shell_sort(array);
	//stat_pyramid += shell_pyramid(array);

	cout << "bubble : " << stat_bubble << endl;
	cout << "shell : " << stat_shell << endl;
	//cout << "pyramid : " << stat_pyramid << endl;
}

//Ќадо сделать пирамидальную, решить что-то по поводу скорости работы, графики