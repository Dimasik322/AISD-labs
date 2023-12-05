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



//select sort �������
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

//select sort ����� ���������
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

//quick sort �������
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

//quick sort ����� ���������
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

//merge sort �������
template<typename T>
stats& merge(vector<T>& array, int begin, int mid, int end) {
	stats sort_stats;
	int n1 = mid - begin + 1;
	int n2 = end - mid;
	vector<T> left(n1);
	vector<T> right(n2);
	sort_stats.copy_count += n1;
	sort_stats.copy_count += n2;
	for (int i(0); i < n1; ++i) {
		left[i] = array[begin + i];
	}
	for (int j(0); j < n2; ++j) {
		right[j] = array[mid + 1 + j];
	}
	int i = 0;
	int j = 0;
	int k = begin;
	while (i<n1 && j<n2) {
		sort_stats.comparison_count += 1;
		if (left[i] <= right[j]){
			array[k] = left[i];
			++i;
		}
		else {
			array[k] = right[j];
			++j;
		}
		++k;
	}
	sort_stats.comparison_count += 1;
	while (i < n1) {
		sort_stats.comparison_count += 1;
		array[k] = left[i];
		++i;
		++k;
	}
	while (j < n2) {
		sort_stats.comparison_count += 1;
		array[k] = right[j];
		++j;
		++k;
	}

	return sort_stats;
}

template<typename T>
stats& merge_sort(vector<T>& array, int begin, int end) {
	stats sort_stats;
	if (begin < end) {
		int mid = begin + (end - begin) / 2;
		sort_stats += merge_sort(array, begin, mid);
		sort_stats += merge_sort(array, mid + 1, end);
		sort_stats += merge(array, begin, mid, end);
	}
	return sort_stats;
}

template<typename T>
stats& merge_sort(vector<T> array) {
	stats sort_stats;
	sort_stats += merge_sort(array, 0, array.size() - 1);
	//cout << array;
	return sort_stats;
}

//merge sort ����� ���������

template<typename Iter, typename T>
stats& merge(vector<T>& array, Iter begin, Iter mid, Iter end) {
	stats sort_stats;
	vector<T> new_array(distance(begin, end));
	auto i = begin;
	auto j = mid;
	auto k = new_array.begin();
	while (i < mid && j < end) {
		sort_stats.comparison_count += 1;
		if (*i < *j) {
			*k = *i;
			++k;
			++i;
		}
		else {
			*k = *j;
			++k;
			++j;
		}
	}
	sort_stats.comparison_count += 1;
	while (i < mid) {
		sort_stats.comparison_count += 1;
		*k = *i;
		sort_stats.copy_count += 1;
		++k;
		++i;
	}
	sort_stats.comparison_count += 1;
	while (j < end) {
		sort_stats.comparison_count += 1;
		*k = *j;
		sort_stats.copy_count += 1;
		++k;
		++j;
	}
	sort_stats.comparison_count += 1;
	sort_stats.copy_count += 1;
	copy(new_array.begin(), new_array.end(), begin);
	/*Iter l = begin;
	while (l != end) {
		cout << *l << " ";
		++l;
	}
	cout << endl;*/
	return sort_stats;
}

//merge sort ����� ���������
template<typename Iter, typename T>
stats& merge_sort(vector<T>& arr, Iter begin, Iter end) {
	stats sort_stats;
	if (distance(begin, end) > 1) {
		sort_stats.comparison_count += 1;
		auto mid = begin + (distance(begin, end) / 2);
		sort_stats += merge_sort(arr, begin, mid);
		sort_stats += merge_sort(arr, mid, end);
		sort_stats += merge(arr, begin, mid, end);
	}
	return sort_stats;
}

//template<typename T>
//stats& merge_sort(vector<T> arr) {
//	stats sort_stats;
//	sort_stats += merge_sort(arr, arr.begin(), arr.end());
//	cout << arr;
//	return sort_stats;
//}


template<typename T>
vector<T> random_array(const int& len) {
	if (len <= 0) {
		throw length_error("������ �� ����� ���� ������������� ��� �������");
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
		throw length_error("������ �� ����� ���� ������������� ��� �������");
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
		throw length_error("������ �� ����� ���� ������������� ��� �������");
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
		throw length_error("������ �� ����� ���� ������������� ��� �������");
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
		throw length_error("������ �� ����� ���� ������������� ��� �������");
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
		throw length_error("������ �� ����� ���� ������������� ��� �������");
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
		throw length_error("������ �� ����� ���� ������������� ��� �������");
	}
	cout << len << ":" << endl;

	stats stat_select;
	stats stat_quick;
	stats stat_merge;

	for (int i(0); i < 100; ++i) {
		cout << i + 1 << "/" << 100 << endl;
		vector<T> array = random_array<T>(len);
		//stat_select += selection_sort(array);
		stat_quick += quick_sort(array);
		stat_merge += merge_sort(array);
	}

	stat_select /= 100;
	stat_quick /= 100;
	stat_merge /= 100;

	cout << "selection : " << stat_select << endl;
	cout << "quick : " << stat_quick << endl;
	cout << "merge : " << stat_merge << endl;
}

template<typename T>
void compare_sort_sorted(const int& len, const bool& reverse) {
	if (len <= 0) {
		throw length_error("������ �� ����� ���� ������������� ��� �������");
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