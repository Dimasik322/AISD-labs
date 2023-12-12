#pragma once

#include <vector>
#include <iostream>
#include <random>
#include <exception>



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



//select sort обычная
template<typename T>
stats& selection_sort(vector<T> array) {
	stats sort_stats;
	for (int i(0); i < array.size()-1; ++i) {
		sort_stats.comparison_count += 1;
		int min_index = i;
		for (int j(i + 1); j < array.size(); ++j) {
			sort_stats.comparison_count += 1;
			if (array[min_index] > array[j]) {

				min_index = j;
			}
			sort_stats.comparison_count += 1;
		}
		if (min_index != i) {
			swap(array[i], array[min_index]);
		}
	}
	return sort_stats;
}

//select sort через итераторы
template<typename Iter>
stats& selection_sort(Iter begin, Iter end) {
	stats sort_stats;
	for (auto i(begin); i != end - 1; ++i) {
		sort_stats.comparison_count += 1;
		auto min_iter = i;
		for (auto j(i + 1); j != end; ++j) {
			sort_stats.comparison_count += 1;
			if (*j < *min_iter) {
				min_iter = j;
			}
			sort_stats.comparison_count += 1;
		}
		sort_stats.comparison_count += 1;
		if (min_iter != i) {
			swap(*min_iter, *i);
			sort_stats.copy_count += 3;
		}
		sort_stats.comparison_count += 1;
	}
	sort_stats.comparison_count += 1;
	return sort_stats;
}

/*template<typename T>
stats& selection_sort(vector<T> array) {
	stats sort_stats;
	sort_stats += selection_sort(array.begin(), array.end());
	cout << array;
	return selection_sort;
}*/

//quick sort обычная
template<typename T>
stats& quick_sort(T* array, int size) {
	stats sort_stats;
	if (size <= 1) {
		return sort_stats;
	}
	sort_stats.copy_count += 1;
	T pivot = array[0];
	int i = 0;
	int j = size - 1;
	while (i <= j) {
		while (array[i] < pivot) {
			sort_stats.comparison_count += 1;
			++i;
		}
		while (array[j] > pivot) {
			sort_stats.comparison_count += 1;
			--j;
		}
		//cout << array[i] << " " << array[j] << endl;
		if (i <= j) {
			swap(array[i], array[j]);
			++i;
			--j;
		}
		sort_stats.comparison_count += 1;
		/*for (int k(0); k < size; ++k) {
			cout << *(array + k) << " ";
		}
		cout << endl;*/
	}

	sort_stats += quick_sort(array, j + 1);
	sort_stats += quick_sort(array + i, size - i);

	return sort_stats;
}

template<typename T>
stats& quick_sort(vector<T> array) {
	stats sort_stats;
	sort_stats += quick_sort(&array[0], array.size());
	//cout << array;
	return sort_stats;
}

//quick sort через итераторы
template<typename Iter>
stats& quick_sort(Iter begin, Iter end) {
	stats sort_stats;
	if (begin == end) {
		sort_stats.comparison_count += 1;
		return sort_stats;
	}
	/*Iter k = begin;
	while (k != end) {
		cout << *k << " ";
		++k;
	}
	cout << endl;*/
	Iter pivot = begin;
	Iter i = begin + 1;
	Iter j = end;
	while (i != j) {
		sort_stats.comparison_count += 1;
		if (*i < *pivot) {
			++i;
		}
		else {
			--j;
			while (i != j && *j >= *pivot) {
				sort_stats.comparison_count += 1;
				--j;
				//cout << *i << " " << *j << " " << *pivot << endl;
			}
			sort_stats.comparison_count += 1;
			swap(*i, *j);
			sort_stats.copy_count += 3;
		}
		sort_stats.comparison_count += 1;
	}
	sort_stats.comparison_count += 1;
	--i;
	swap(*begin, *i);
	sort_stats.copy_count += 3;
	sort_stats.comparison_count += 1;

	sort_stats += quick_sort(begin, i);
	sort_stats += quick_sort(j, end);

	return sort_stats;
}

/*template<typename T>
stats& quick_sort(vector<T> array) {
	stats sort_stats;
	sort_stats += quick_sort(array.begin(), array.end());
	cout << array;
	return sort_stats;
}*/

template<typename T>
stats merge(vector<T>& arr, int i, int j) {
	stats sort_stats;
	if (i + j >= arr.size()) {
		j = 1;
	}
	vector<T> right(arr.end() - j, arr.end());
	vector<T> left(arr.begin(), arr.begin() + i);
	sort_stats.copy_count += i;
	sort_stats.copy_count += j;
	int n1 = left.size();
	int n2 = right.size();
	int count_left = 0;
	int count_right = 0;
	arr.erase(arr.end() - j, arr.end());
	arr.erase(arr.begin(), arr.begin() + i);
	while (count_left < n1 && count_right < n2) {
		sort_stats.comparison_count += 1;
		if (left[left.size() - 1 - count_left]>right[count_right]) {
			arr.insert(arr.begin(), left[left.size() - 1 - count_left]);
			++count_left;
		}
		else {
			arr.insert(arr.begin(), right[count_right]);
			++count_right;
		}
	}
	while (count_left < n1) {
		sort_stats.comparison_count += 1;
		arr.insert(arr.begin(), left[left.size() - 1 - count_left]);
		++count_left;
	}
	while (count_right < n2) {
		sort_stats.comparison_count += 1;
		arr.insert(arr.begin(), right[count_right]);
		++count_right;
	}
	//cout << arr;
	return sort_stats;
}

template<typename T>
stats merge_sort(vector<T>& arr, int begin, int end) {
	stats sort_stats;
	int i_first = begin;
	int i_last = begin;
	int j_first = end;
	int j_last = end;
	while (i_last < end && arr[i_last] < arr[i_last + 1]) {
		sort_stats.comparison_count += 1;
		++i_last;
	}
	while (j_first > begin && arr[j_first] < arr[j_first - 1]) {
		sort_stats.comparison_count += 1;
		--j_first;
	}
	if (i_last == arr.size() - 1) {
		return sort_stats;
	}
	else {
		sort_stats += merge(arr, i_last + 1, j_last - j_first + 1);
		sort_stats += merge_sort(arr, 0, arr.size() - 1);
		return sort_stats;
	}
}

template<typename T>
stats merge_sort(vector<T> arr) {
	stats sort_stats;
	//sort_stats += 
	sort_stats += merge_sort(arr, 0, arr.size() - 1);
	cout << arr;
	return sort_stats;
}

template<typename T>
vector<T> random_array(const int& len) {
	if (len <= 0) {
		throw length_error("Массив не может быть отрицательным или нулевым");
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
		throw length_error("Массив не может быть отрицательным или нулевым");
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
		throw length_error("Массив не может быть отрицательным или нулевым");
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
		throw length_error("Массив не может быть отрицательным или нулевым");
	}
	vector<string> array{};
	array.reserve(len);
	for (int i(0); i < len; ++i) {
		string str{};
		for (int j(0); j < 10; ++j) {
			str += char((int)(rand()) * 26 / RAND_MAX + 97);
		}
		array.emplace_back(str);
	}
	return array;
}

template<typename T>
vector<T> sorted_array(const int& len, const bool& reverse) {
	if (len <= 0) {
		throw length_error("Массив не может быть отрицательным или нулевым");
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
		throw length_error("Массив не может быть отрицательным или нулевым");
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
		throw length_error("Массив не может быть отрицательным или нулевым");
	}
	cout << len << ":" << endl;

	stats stat_select;
	stats stat_quick;
	stats stat_merge;

	for (int i(0); i < 100; ++i) {
		cout << i + 1 << "/" << 100 << endl;
		vector<T> array = random_array<T>(len);
		stat_select += selection_sort(array);
		stat_quick += quick_sort(array);
		//stat_merge += merge_sort(array);
	}

	stat_select /= 100;
	stat_quick /= 100;
	//stat_merge /= 100;

	cout << "selection : " << stat_select << endl;
	cout << "quick : " << stat_quick << endl;
	cout << "merge : " << stat_merge << endl;
}

template<typename T>
void compare_sort_sorted(const int& len, const bool& reverse) {
	if (len <= 0) {
		throw length_error("Массив не может быть отрицательным или нулевым");
	}

	stats stat_select;
	stats stat_quick;
	stats stat_merge;

	vector<T> array = sorted_array<T>(len, reverse);

	if (reverse == true) {
		cout << len << " reverse sorted:" << endl;
	}
	else {
		cout << len << " sorted:" << endl;
	}

	stat_select += selection_sort(array);
	stat_quick += quick_sort(array);
	stat_merge += merge_sort(array);

	cout << "selection : " << stat_select << endl;
	cout << "quick : " << stat_quick << endl;
	cout << "merge : " << stat_merge << endl;
}
