#pragma once

#include <iostream>
#include <exception>

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

	Node* copy(Node*& ptr) {
		if (ptr == nullptr) {
			return nullptr;
		}
		auto tmp = new Node(ptr->value);
		tmp->left = copy(ptr->left);
		tmp->right = copy(ptr->right);
		return tmp;
	}
	void delete_set(Node*& ptr) {
		if (ptr == nullptr) {
			return;
		}
		delete_set(ptr->left);
		delete_set(ptr->right);
		//cout<< endl << "del " << ptr->value;
		delete ptr;
		ptr = nullptr;
	}
	int height(Node*& ptr) {
		if (ptr == nullptr) {
			return 0;
		}
		return max(height(ptr->left), height(ptr->right)) + 1;
	}
	int ratio(Node*& ptr) {
		if (ptr == nullptr) {
			return 0;
		}
		return (height(ptr->left) - height(ptr->right));
	}
	Node*& rotate_left(Node*& ptr) {
		auto tmp = ptr->right;
		ptr->right = tmp->left;
		tmp->left = ptr;
		return tmp;
	}
	Node*& rotate_right(Node*& ptr) {
		auto tmp = ptr->left;
		ptr->left = tmp->right;
		tmp->right = ptr;
		return tmp;
	}
	Node*& balance(Node*& ptr) {
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

	Node* erase(Node* ptr, const int& value) {
		if (ptr == nullptr) {
			throw invalid_argument("Cannot erase non-existent value");
		}
		if (value < ptr->value) {
			ptr->left = erase(ptr->left, value);
		}
		else if (value > ptr->value) {
			ptr->right = erase(ptr->right, value);
		}
		else {
			//???????????????????????????????????
		}
		return balance(ptr);
	}
	Node* insert(Node*& ptr, const int& value) {
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
	void print(Node*& ptr) {
		if (ptr != nullptr) {
			cout << ptr->value << " ";
			this->print(ptr->left);
			this->print(ptr->right);
		}
		else {
			cout << "- ";
		}
	}
	bool contains(Node*& ptr, const int& value) {
		if (ptr == nullptr) {
			return false;
		}
		if (ptr->value != value) {
			return true;
		}
		if (value > ptr->value) {
			return contains(ptr->right, value);
		}
		else {
			return contains(ptr->right, value);
		}
	}

public:
	my_set() : head(nullptr) {};
	my_set(my_set& other) {
		head = copy(other.head);
	}
	~my_set() {
		cout << "Destruct set";
		delete_set(head);
	}

	void operator=(my_set& other) {
		delete_set(head);
		head = copy(other.head);
	}

	void insert(const int& value) {
		head = insert(head, value);
	}
	void print() {
		print(head);
		cout << endl;
	}
	bool contains(const int& value) {
		return contains(head, value);
	}
	void erase(const int& value) {
		head = erase(head, value);
	}
};

vector<int, int>& get_unique(vector<int, int>& vec) {
	//?????????????????????????
}

//Надо доделать erase, функцию для неповторяющихся элементов