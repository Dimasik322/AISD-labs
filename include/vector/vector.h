#pragma once

#include <random>
#include <iostream>
#include <stdexcept>

using namespace std;

template<typename T>
class Coef {
public:
	T coef;
	int power;

	Coef(const T& coef, const int& power) :coef(coef), power(power) {};

	void operator=(const Coef<T>& rhs) {
		if (rhs.power == 0) {
			throw invalid_argument("Степень не может быть равна 0");
		}
		else {
			this->coef = rhs.coef;
			this->power = rhs.power;
		}
	}
};

template <typename T>
bool operator==(const Coef<T>& lhs, const Coef<T>& rhs) {
	if (lhs.coef == rhs.coef && lhs.power == rhs.power) {
		return true;
	}
	else {
		return false;
	}
}

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

	Node<T>* get_head() const {
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
		LinkedList<T> new_list;
		if (other.head != nullptr) {
			Node<T>* tmp_other = other.head;
			while (tmp_other) {
				new_list.push_tail(tmp_other->value);
				tmp_other = tmp_other->next;
			}
		}
		if (this->head != nullptr) {
			Node<T>* tmp_this = this->head;
			while (tmp_this) {
				new_list.push_tail(tmp_this->value);
				tmp_this = tmp_this->next;
			}
		}
		while (head) {
			Node<T>* tmp = head;
			head = head->next;
			delete tmp;
			tmp = nullptr;
		}
		this->head = new_list.head;
		new_list.head = nullptr;
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
class LinkedList<Coef<T>>{
private:
	Node<Coef<T>>* head;

public:
	LinkedList() {
		head = nullptr;
	}
	LinkedList(const LinkedList<Coef<T>>& other) {
		head = nullptr;
		Node<Coef<T>>* tmp_other = other.head;
		while (tmp_other) {
			this->push_tail(tmp_other->value);
			tmp_other = tmp_other->next;
		}
	}
	LinkedList(const int size, const int rand_max, const int max_power) {
		head = nullptr;
		int count = 0;
		while (count != size) {
			this->push_tail(Coef<int>((int)(rand()) * rand_max / RAND_MAX + 1, (int)(rand()) * max_power / RAND_MAX + 1));
			count += 1;
		}
	}
	LinkedList(const int size, const float rand_max, const int max_power) {
		head = nullptr;
		int count = 0;
		while (count != size) {
			this->push_tail(Coef<float>((float)(rand()) * (rand_max - 0.0001f) / RAND_MAX + 0.0001f, (int)(rand()) * max_power / RAND_MAX + 1));
			count += 1;
		}
	}

	~LinkedList() {
		while (head) {
			Node<Coef<T>>* tmp = head;
			//cout << "delete" << tmp->value << " " << tmp << endl;
			head = head->next;
			delete tmp;
			tmp = nullptr;
		}
	}

	Node<Coef<T>>* get_head() const {
		return head;
	}
	Coef<T>& operator[](const int index) {
		Node<Coef<T>>* tmp = head;
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

	void push_tail(const Coef<T>& value) {
		if (value.power == 0) {
			return;
		}
		Node<Coef<T>>* newNode = new Node<Coef<T>>(value);
		if (head == nullptr) {
			head = newNode;
		}
		else {
			Node<Coef<T>>* current = head;
			while (current->next != nullptr) {
				current = current->next;
			}
			newNode->prev = current;
			current->next = newNode;

		}
	}
	void push_head(const Coef<T>& value) {
		if (value.power == 0) {
			return;
		}
		Node<Coef<T>>* newNode = new Node<Coef<T>>(value);
		if (head == nullptr) {
			head = newNode;
		}
		else {
			Node<Coef<T>>* current = head;
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
				Node<Coef<T>>* tmp = head;
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
			Node<Coef<T>>* last = head;
			while (last->next != nullptr) {
				last = last->next;
			}
			Node<Coef<T>>* pre_last = last->prev;
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
	void push_tail(const LinkedList<Coef<T>>& other) {
		if (other.head != nullptr) {
			Node<Coef<T>>* tmp_other = other.head;
			while (tmp_other) {
				this->push_tail(tmp_other->value);
				tmp_other = tmp_other->next;
			}
		}
	}
	void push_head(const LinkedList<Coef<T>>& other) {
		LinkedList<Coef<T>> new_list;
		if (other.head != nullptr) {
			Node<Coef<T>>* tmp_other = other.head;
			while (tmp_other) {
				new_list.push_tail(tmp_other->value);
				tmp_other = tmp_other->next;
			}
		}
		if (this->head != nullptr) {
			Node<Coef<T>>* tmp_this = this->head;
			while (tmp_this) {
				new_list.push_tail(tmp_this->value);
				tmp_this = tmp_this->next;
			}
		}
		while (head) {
			Node<Coef<T>>* tmp = head;
			head = head->next;
			delete tmp;
			tmp = nullptr;
		}
		this->head = new_list.head;
		new_list.head = nullptr;
	}
	void delete_node(const Coef<T>& x) {
		if (head != nullptr) {
			Node<Coef<T>>* current = head;
			Node<Coef<T>>* tmp = nullptr;
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

	void operator=(const LinkedList<Coef<T>>& other) {
		Node<Coef<T>>* current = head;
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

	T get_value(const T x) {
		T sum = 0;
		auto current = head;
		while (current) {
			sum = sum + (current->value.coef * pow(x, current->value.power));
			current = current->next;
		}
		return sum;
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
	while (tmp != nullptr) {
		os << tmp->value << " ";
		tmp = tmp->next;
	}
	return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, Coef<T>& rhs)
{
	os << rhs.coef << "*x^" << rhs.power;
	return os;
}