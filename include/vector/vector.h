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
			Node<T>* tmp = head;
			head = head->next;
			head->prev = nullptr;
			delete tmp;
			tmp = nullptr;
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
	void delete_node(const T& value) {
		if (head != nullptr) {
			Node<T>* current = head;
			Node<T>* tmp = nullptr;
			while (current != nullptr) {
				if (current->value == value) {
					if (current->prev != nullptr) {
						current->prev->next = current->next;
					}
					else {
						this->pop_head();
					}
					if (current->next != nullptr) {
						current->next->prev = current->prev;
					}
					delete current;
				}
				current = current->next;
			}
		}
		else {
			throw length_error("Empty list");
		}
	}

};

template<typename T>
std::ostream& operator<<(std::ostream& os, LinkedList<T>& rhs)
{
	Node<T>* tmp = rhs.get_head();
	while (tmp != nullptr){
		os << tmp->value << " ";
		tmp = tmp->next;
	}
	return os;
}