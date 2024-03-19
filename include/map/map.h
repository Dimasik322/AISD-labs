#pragma once

#include <iostream>
#include <exception>

template<typename K, typename T>
struct Pair {
	K key;
	T value;
	Pair<K,T>* next;

	Pair<K, T>(const K& key, const T& value) : key(key), value(value), next(nullptr) {};
	Pair<K, T>() {

	}
};

template<typename K, typename T>
class Map {
private:
	size_t _size;
	Pair<K, T>** _buskets;

	size_t hash(const K& key) const {
		return key % _size;
	}

public:
	Map<K, T>() {
		_size = 10;
		_buskets = new Pair<K, T>*[_size];
		for (int i(0); i < _size; ++i) {
			_buskets[i] = nullptr;
		}
	};
	Map<K, T>(const size_t size) {
		_size = size;
		_buskets = new Pair*[_size];
		for (int i(0); i < size; ++i) {
			_buskets[i] = nullptr;
		}
	}
	~Map<K, T>() {
		clear();
		delete _buskets;
	}

	void clear() {
		Pair<K, T>* tmp = nullptr;
		for (int i(0); i < _size; ++i) {
			tmp = _buskets[i];
			while (tmp) {
				auto tmp_next = tmp->next;
				delete tmp;
				tmp = tmp_next;
			}
		}
	}
	void insert(const K& key, const T& value) {
		auto new_pair = new Pair<K, T>(key, value);
		int index = hash(key);
		new_pair->next = _buskets[index];
		_buskets[index] = new_pair;
	}
	void print() const {
		Pair<K, T>* tmp = nullptr;
		for (int i(0); i < _size; ++i) {
			tmp = _buskets[i];
			while (tmp) {
				std::cout << tmp->key << " : " << tmp->value << std::endl;
				tmp = tmp->next;
			}
		}
	}
};




