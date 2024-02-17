#pragma once

#include <iostream>
#include <exception>
#include <vector>
#include <ctime>

using namespace std;

class Node {
public:
	int value;
	Node* left;
	Node* right;

	Node(int _value, Node* _left, Node* _right) : value(_value), left(_left), right(_right) {};
	Node() :value(0), left(nullptr), right(nullptr) {};
	Node(int _value) : value(_value), left(nullptr), right(nullptr) {};
};

class my_set {
private:
	Node* head;

	Node* copy(Node* ptr) {
		if (ptr == nullptr) {
			return nullptr;
		}
		auto tmp = new Node(ptr->value);
		tmp->left = copy(ptr->left);
		tmp->right = copy(ptr->right);
		return tmp;
	}
	void delete_set(Node* ptr) {
		if (ptr == nullptr) {
			return;
		}
		delete_set(ptr->left);
		delete_set(ptr->right);
		//cout<< endl << "del " << ptr->value;
		delete ptr;
	}
	int height(Node* ptr) {
		if (ptr == nullptr) {
			return 0;
		}
		return std::max(height(ptr->left), height(ptr->right)) + 1;
	}
	int ratio(Node* ptr) {
		if (ptr == nullptr) {
			return 0;
		}
		return (height(ptr->left) - height(ptr->right));
	}
	Node* rotate_left(Node* ptr) {
		auto tmp = ptr->right;
		ptr->right = tmp->left;
		tmp->left = ptr;
		return tmp;
	}
	Node* rotate_right(Node* ptr) {
		auto tmp = ptr->left;
		ptr->left = tmp->right;
		tmp->right = ptr;
		return tmp;
	}
	Node* balance(Node* ptr) {
		auto x = ratio(ptr);
		if (x > 1) {
			if (ratio(ptr->left) >= 0) {
				return rotate_right(ptr);
			}
			else {
				ptr->left = rotate_left(ptr->left);
				return rotate_right(ptr);
			}
		}
		if (x < -1) {
			if (ratio(ptr->right) <= 0) {
				return rotate_left(ptr);
			}
			else {
				ptr->right = rotate_right(ptr->right);
				return rotate_left(ptr);
			}
		}
		return ptr;
	}
	Node* min(Node* ptr) {
		while (ptr->left != nullptr) {
			ptr = ptr->left;
		}
		return ptr;
	}
	Node* max(Node* ptr) {
		while (ptr->right != nullptr) {
			ptr = ptr->right;
		}
		return ptr;
	}
	void to_vector(Node* ptr, vector<int>& vec) {
		if (ptr == nullptr) {
			return;
		}
		vec.push_back(ptr->value);
		to_vector(ptr->left, vec);
		to_vector(ptr->right, vec);

	}

	Node* erase(Node* ptr, const int value) {
		if (ptr == nullptr) {
			return nullptr;
		}
		if (value < ptr->value) {
			ptr->left = erase(ptr->left, value);
		}
		else if (value > ptr->value) {
			ptr->right = erase(ptr->right, value);
		}
		else {
			if (ptr->left == nullptr || ptr->right == nullptr) {
				Node* tmp;
				if (ptr->left != nullptr) {
					tmp = ptr->left;
				}
				else {
					tmp = ptr->right;
				}
				if (tmp == nullptr) {
					tmp = ptr;
					ptr = nullptr;
				}
				else {
					*ptr = *tmp;
				}
				delete tmp;
			}
			else {
				auto tmp = min(ptr->right);
				ptr->value = tmp->value;
				ptr->right = erase(ptr->right, tmp->value);
			}

		}
		return balance(ptr);
	}
	Node* insert(Node* ptr, const int value) {
		if (ptr == nullptr) {
			return new Node(value);
		}
		if (value < ptr->value) {
			ptr->left = insert(ptr->left, value);
		}
		else if (value > ptr->value) {
			ptr->right = insert(ptr->right, value);
		}
		else {
			return ptr;
		}
		return balance(ptr);
	}
	void print(Node* ptr) {
		if (ptr != nullptr) {
			cout << ptr->value << " ";
			this->print(ptr->left);
			this->print(ptr->right);
		}
		else {
			cout << "- ";
		}
	}
	bool contains(Node* ptr, const int value) {
		if (ptr == nullptr) {
			return false;
		}
		if (ptr->value == value) {
			return true;
		}
		if (value > ptr->value) {
			return contains(ptr->right, value);
		}
		else {
			return contains(ptr->left, value);
		}
	}

public:
	my_set() : head(nullptr) {};
	my_set(my_set& other) {
		head = copy(other.head);
	}
	~my_set() {
		//cout << "Destruct set";
		delete_set(head);
		head = nullptr;
	}

	void operator=(my_set& other) {
		delete_set(head);
		head = copy(other.head);
	}
	int min() {
		return min(head)->value;
	}
	int max() {
		return max(head)->value;
	}
	void clear() {
		delete_set(head);
		head = nullptr;
	}
	vector<int> to_vector() {
		vector<int> vec;
		to_vector(head, vec);
		return vec;
	}

	bool insert(const int value) {
		if (contains(value)) {
			return false;
		}
		else {
			head = insert(head, value);
			return true;
		}
	}
	void print() {
		print(head);
		cout << endl;
	}
	bool contains(const int value) {
		return contains(head, value);
	}
	bool erase(const int value) {
		if (!contains(value)) {
			return false;
		}
		else {
			head = erase(head, value);
			return true;
		}
	}
};

size_t lcg() {
	static size_t x = 0;
	x = (1021 * x + 24631) % 116640;
	return x;
}

void compare(int lenght) {
	unsigned int vec_time = 0;
	unsigned int set_time = 0;
	unsigned int time;	

	vector<int> vec;
	my_set set;
	for (int i(0); i < 100; ++i) {
		//cout << i;
		for (int j(0); j < lenght; ++j) {
			//cout << j << " ";
			int value = lcg();
			//cout << value << endl;

			time = clock();
			vec.push_back(value);
			vec_time += clock() - time;

			time = clock();
			set.insert(value);
			set_time += clock() - time;
		}
		vec.clear();
		set.clear();
	}
	cout << "Insertion:" << endl;
	cout << "vector : " << double(vec_time) / 100.0 <<" ms" << endl;
	cout << "set : " << double(set_time) / 100.0 <<" ms" << endl;

	vec_time = 0;
	set_time = 0;

	for (int i(0); i < lenght; ++i) {
		int value = lcg();
		vec.push_back(value);
		set.insert(value);
	}
	bool flag = false;
	for (int i(0); i < 1000; ++i) {
		//cout << i;
		int value = lcg();

		time = clock();
		for (int j = 0; j != vec.size(); ++j) {
			if (vec[j] == value) {
				break;
			}
		}
		vec_time += clock() - time;

		time = clock();
		flag = set.contains(value);
		set_time += clock() - time;
	}
	vec.clear();
	set.clear();
	cout << "Search:" << endl;
	cout << "vector : " << double(vec_time) / 100.0 << " ms" << endl;
	cout << "set : " << double(set_time) / 100.0 << " ms" << endl;

	vec_time = 0;
	set_time = 0;

	for (int i(0); i < lenght; ++i) {
		int value = lcg();
		vec.push_back(value);
		set.insert(value);
	}
	for (int i(0); i < 1000; ++i) {
		//cout << i;
		int value = lcg();

		time = clock();
		vec.push_back(value);
		vec.pop_back();
		vec_time += clock() - time;

		time = clock();
		set.insert(value);
		set.erase(value);
		set_time += clock() - time;
	}
	vec.clear();
	set.clear();
	cout << "Insertion & erasing:" << endl;
	cout << "vector : " << double(vec_time) / 100.0 << " ms" << endl;
	cout << "set : " << double(set_time) / 100.0 << " ms" << endl;
}

vector<int> get_unique(vector<int> vec) {
	auto set_repeat = my_set();
	auto set_unique = my_set();

	for (int i(0); i < vec.size(); ++i) {
		if (!set_unique.contains(vec[i]) && !set_repeat.contains(vec[i])) {
			set_unique.insert(vec[i]);
		}
		else {
			if (set_unique.contains(vec[i]) && !set_repeat.contains(vec[i])) {
				set_unique.erase(vec[i]);
				set_repeat.insert(vec[i]);
			}
		}
	}

	vector<int> unique = set_unique.to_vector();
	return unique;
}