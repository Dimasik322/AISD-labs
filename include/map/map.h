#pragma once

#include <iostream>
#include <exception>


struct Pair {
	int key;
	int value;
	Pair* next;

	Pair(const int& key, const int& value) : key(key), value(value), next(nullptr) {};
};

class Map {
private:
	size_t _size;
	Pair** _buskets;
	
	size_t hash(const int& key) const {
		//Тут в return пишешь свою функцию хэша
		return 0;
	}
	void copy(const Map& other) {
		for (size_t i(0); i < _size; ++i) {
			Pair* tmp = other._buskets[i];
			while (tmp) {
				insert(tmp->key, tmp->value);
				tmp = tmp->next;
			}
		}
	}

public:
	Map() {
		_size = 10;
		_buskets = new Pair*[_size];
		for (size_t i(0); i < _size; ++i) {
			_buskets[i] = nullptr;
		}
	};
	Map(const size_t& size) {
		_size = size;
		_buskets = new Pair*[_size];
		for (size_t i(0); i < size; ++i) {
			_buskets[i] = nullptr;
		}
	}
	Map(const Map& other) {
		_size = other._size;
		_buskets = new Pair*[_size];
		for (size_t i(0); i < _size; ++i) {
			_buskets[i] = nullptr;
		}
		copy(other);
	}
	Map(const size_t& size, const unsigned& seed) {
		_size = size;
		_buskets = new Pair* [_size];
		for (size_t i(0); i < size; ++i) {
			_buskets[i] = nullptr;
		}

		srand(seed);
		size_t count = 0;
		while (count != 256) {
			unsigned x = unsigned(rand() % 256);
			if (!this->contains(x)) {
				this->insert(count, x);
				++count;
			}
		}
	}
	~Map() {
		clear();
		delete [] _buskets;
	}

	Map& operator=(const Map& other) {
		if (&other == this) {
			return *this;
		}
		clear();
		delete [] _buskets;
		_size = other._size;
		_buskets = new Pair* [_size];
		for (size_t i(0); i < _size; ++i) {
			_buskets[i] = nullptr;
		}
		copy(other);
		return *this;
	}

	void clear() {
		Pair* tmp = nullptr;
		for (size_t i(0); i < _size; ++i) {
			tmp = _buskets[i];
			while (tmp) {
				auto tmp_next = tmp->next;
				delete tmp;
				tmp = tmp_next;
			}
		}
	}

	void insert(const int& key, const int& value) const {
		size_t index = hash(key);
		auto tmp = _buskets[index];
		if (!tmp) {
			_buskets[index] = new Pair(key, value);
			return;
		}
		while (tmp) {
			if (tmp->key == key) {
				throw std::invalid_argument("This key already in map");
			}
			if (tmp->next) {
				tmp = tmp->next;
			}
			else {
				tmp->next = new Pair(key, value);
				return;
			}
		}
	}
	void insert_or_assign(const int& key, const int& value) const {
		size_t index = hash(key);
		auto tmp = _buskets[index];
		if (!tmp) {
			_buskets[index] = new Pair(key, value);
			return;
		}
		while (tmp) {
			if (tmp->key == key) {
				tmp->value = value;
				return;
			}
			if (tmp->next) {
				tmp = tmp->next;
			}
			else {
				tmp->next = new Pair(key, value);
				return;
			}
		}
	}
	bool contains(const int& value) const {
		for (size_t index(0); index < _size; ++index) {
			auto tmp = _buskets[index];
			while (tmp) {
				if (tmp->value == value){
					return true;
				}
				tmp = tmp->next;
			}
		}
		return false;
	}
	int* search(const int& key) {
		size_t index = hash(key);
		auto tmp = _buskets[index];
		if (tmp == nullptr) {
			return nullptr;
		}
		while (tmp) {
			if (tmp->key == key) {
				return &tmp->value;
			}
			tmp = tmp->next;
		}
		return nullptr;
	}
	bool erase(const int& key) const {
		size_t index = hash(key);
		auto tmp = _buskets[index];
		if (tmp == nullptr) {
			return false;
		}
		if (tmp->key == key) {
			_buskets[index] = tmp->next;
			delete tmp;
			return true;
		}
		Pair* prev = nullptr;
		while (tmp) {
			if (tmp->key == key) {
				prev->next = tmp->next;
				delete tmp;
				return true;
			}
			prev = tmp;
			tmp = tmp->next;
		}
		return false;
	}
	int count(const int& key) {
		size_t index = hash(key);
		auto tmp = _buskets[index];
		while (tmp) {
			if (tmp->key == key) {
				return 1;
			}
			tmp = tmp->next;
		}
		return 0;
	}
	void print() const {
		Pair* tmp = nullptr;
		for (size_t i(0); i < _size; ++i) {
			tmp = _buskets[i];
			while (tmp) {
				std::cout << tmp->key << " : " << tmp->value << std::endl;
				tmp = tmp->next;
			}
		}
	}
};

char pearson_hash(Map map, const std::string& str) {
	char hash = str.length();
	for (char c : str) {
		hash = *map.search((hash + (unsigned)c) % 256);
	}
	return hash;
}

bool is_equal(const std::string& left, const std::string& right) {
	auto map = Map(16, time(NULL));
	if (pearson_hash(map, left) == pearson_hash(map, right)) {
		return true;
	}
	else {
		return false;
	}
}

