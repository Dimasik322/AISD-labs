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
	void print(Node*& ptr) {
		if (ptr != nullptr) {
			cout << ptr->value << " ";
			this->print(ptr->left);
			this->print(ptr->right);
		}
	}
	void insert(Node*& ptr, const int& value) {
		if (ptr == nullptr) {
			auto new_node = new Node(value);
			ptr = new_node;
			return;
		}
		if (value > ptr->value) {
			insert(ptr->right, value);
		}
		else {
			insert(ptr->left, value);
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
	Node* copy(Node*& ptr) {
		if (ptr == nullptr) {
			return nullptr;
		}
		auto tmp = new Node(ptr->value);
		tmp->left = copy(ptr->left);
		tmp->right = copy(ptr->right);
		return tmp;
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

	void print() {
		print(head);
		cout << endl;
	}
	void insert(const int& value) {
		insert(head, value);
	}
	bool contains(const int& value) {
		return contains(head, value);
	}
};

//Надо сделать erase и балансировку, функцию для неповторяющихся элементов