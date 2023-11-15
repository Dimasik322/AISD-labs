#pragma once

#include <random>
#include <iostream>
#include <stdexcept>

using namespace std;

template<typename T>
class Node {
public:
	T value;
	Node<T>* next;
	Node<T>* prev;
	Node<T>(const T& value) :value(value), next(nullptr), prev(nullptr) {};
};

template<typename T>
class LinkedList {
private:
	Node<T>* head;

public:
	LinkedList() {
		head = nullptr;
	}
	LinkedList(const LinkedList<T>& other) {
		head = nullptr;
		Node<T>* tmp_other = other.head;
		while (tmp_other) {
			this->push_tail(tmp_other->value);
			tmp_other = tmp_other->next;
		}
	}
	LinkedList(const int size, const int rand_max) {
		head = nullptr;
		int count = 0;
		while (count != size) {
			this->push_tail((int)(rand()) * rand_max / RAND_MAX + 1);
			count += 1;
		}
	}
	LinkedList(const int size, const float rand_max) {
		head = nullptr;
		int count = 0;
		while (count != size) {
			this->push_tail((float)(rand()) * (rand_max - 0.0001f) / RAND_MAX + 0.0001f);
			count += 1;
		}
	}
	~LinkedList() {
		while (head) {
			Node<T>* tmp = head;
			//cout << "delete" << tmp->value << " " << tmp << endl;
			head = head->next;
			delete tmp;
			tmp = nullptr;
		}
	}

	Node<T>* get_head() const{
		return head;
	}
	T& operator[](const int index) {
		Node<T>* tmp = head;
		int count = 0;
		while (tmp != nullptr) {
			if (count == index) {
				return tmp->value;
			}
			else {
				tmp = tmp->next;
				count += 1;
			}
		}
		throw out_of_range("Index out of range");
	}

	void push_tail(const T& value) {
		Node<T>* newNode = new Node<T>(value);
		if (head == nullptr) {
			head = newNode;
		}
		else {
			Node<T>* current = head;
			while (current->next != nullptr) {
				current = current->next;
			}
			newNode->prev = current;
			current->next = newNode;
			
		}
	}
	void push_head(const T& value) {
		Node<T>* newNode = new Node<T>(value);
		if (head == nullptr) {
			head = newNode;
		}
		else {
			Node<T>* current = head;
			head = newNode;
			head->next = current;
			current->prev = head;
		}
	}
	void pop_head() {
		if (head == nullptr) {
			throw length_error("Cannot delete element in empty list");
		}
		else {
			if (head->next == nullptr) {
				delete head;
				head = nullptr;
			}
			else {
				Node<T>* tmp = head;
				head = head->next;
				head->prev = nullptr;
				delete tmp;
				tmp = nullptr;
			}
		}
	}
	void pop_tail() {
		if (head == nullptr) {
			throw length_error("Cannot delete element in empty list");
		}
		else {
			Node<T>* last = head;
			while (last->next != nullptr) {
				last = last->next;
			}
			Node<T>* pre_last = last->prev;
			if (pre_last != nullptr) {
				pre_last->next = nullptr;
			}
			else {
				head = nullptr;
			}
			delete last;
			last = nullptr;
			

		}
	}
	void push_tail(const LinkedList<T>& other) {
		if (other.head != nullptr) {
			Node<T>* tmp_other = other.head;
			while (tmp_other) {
				this->push_tail(tmp_other->value);
				tmp_other = tmp_other->next;
			}
		}
	}
	void push_head(const LinkedList<T>& other) {
		if (other.head != nullptr) {
			Node<T>* tmp_other = other.head;
			while (tmp_other) {
				this->push_head(tmp_other->value);
				tmp_other = tmp_other->next;
			}
		}
	}
	void delete_node(const T& x) {
		if (head != nullptr) {
			Node<T>* current = head;
			Node<T>* tmp = nullptr;
			while (current != nullptr) {
				tmp = current->next;
				if (current->value == x) {
					if (current->prev == nullptr) {
						this->pop_head();
					}
					else {
						if (current->next == nullptr) {
							this->pop_tail();
						}
						else {
							current->next->prev = current->prev;
							current->prev->next = current->next;
							delete current;
						}
					}
				}
				current = tmp;
			}
		}
		else {
			throw length_error("Empty list");
		}
	}

	void operator=(const LinkedList<T>& other) {
		Node<T>* current = head;
		while (head) {
			head = head->next;
			delete current;
			current = nullptr;
		}
		current = other.head;
		while (current) {
			this->push_tail(current->value);
			current = current->next;
		}
	}

};

template<typename T>
std::ostream& operator<<(std::ostream& os, LinkedList<T>& rhs)
{
	Node<T>* tmp = rhs.get_head();
	if (tmp == nullptr) {
		os << "List is empty";
		return os;
	}
	while (tmp != nullptr){
		os << tmp->value << " ";
		tmp = tmp->next;
	}
	return os;
}

template<typename T>
LinkedList<T> operator+(const LinkedList<T>& lhs, const LinkedList<T>& rhs) {
	LinkedList<T> new_list;
	Node<T>* current = lhs.get_head();
	while (current) {
		new_list.push_tail(current->value);
		current = current->next;
	}
	current = rhs.get_head();
	while (current) {
		new_list.push_tail(current->value);
		current = current->next;
	}
	return new_list;
}

template<typename T>
T get_value(const LinkedList<T>& list, const T x) {
	T sum = 0;
	int count = 0;
	Node<T>* current = list.get_head();
	while (current) {
		sum += (current->value * pow(x, count));
		count += 1;
		current = current->next;
	}
	return sum;
}

template<typename T>
void print(LinkedList<T>& list)
{
	int count = 0;
	Node<T>* current = list.get_head();
	while (current) {
		if (count != 0) {
			cout << " + ";
			cout << current->value << "*" << "x" << "^" << count;
		}
		else {
			cout << current->value;
		}
		count += 1;
		current = current->next;
	}
}

