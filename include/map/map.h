#pragma once

#include <iostream>
#include <exception>

template<typename K, typename T>
struct Pair {
	K key;
	T value;
	Pair<K,T>* next;

	Pair<K, T>(const K& key, const T& value) : key(key), value(value), next(nullptr) {};
	Pair<K, T>() {};
};

template<typename K>
struct Hash {
	size_t operator()(const K& key) const {
		return size_t(key);
	}
};

template<typename K, typename T, typename Hash>
class Map {
private:
	size_t _size;
	Pair<K, T>** _buskets;
	Hash hash;
	
	size_t index_hash(const K& key) const {
		return hash(key) % _size;
	}
	void copy(const Map<K, T, Hash>& other) {
		for (size_t i(0); i < _size; ++i) {
			auto tmp = other._buskets[i];
			while (tmp) {
				insert(tmp->key, tmp->value);
				tmp = tmp->next;
			}
		}
	}

public:
	Map<K, T, Hash>() {
		_size = 10;
		_buskets = new Pair<K, T>*[_size];
		for (size_t i(0); i < _size; ++i) {
			_buskets[i] = nullptr;
		}
	};
	Map<K, T, Hash>(const size_t& size, const unsigned& seed) {
		_size = size;
		_buskets = new Pair<K, T>* [_size];
		for (size_t i(0); i < size; ++i) {
			_buskets[i] = nullptr;
		}
	}
	Map<K, T, Hash>(const size_t& size) {
		_size = size;
		_buskets = new Pair<K, T>*[_size];
		for (size_t i(0); i < size; ++i) {
			_buskets[i] = nullptr;
		}
	}
	Map<K, T, Hash>(const Map<K, T, Hash>& other) {
		_size = other._size;
		_buskets = new Pair<K, T>*[_size];
		for (size_t i(0); i < _size; ++i) {
			_buskets[i] = nullptr;
		}
		copy(other);
	}
	~Map<K, T, Hash>() {
		clear();
		delete [] _buskets;
	}

	Map<K, T, Hash>& operator=(const Map<K, T, Hash>& other) {
		if (&other == this) {
			return *this;
		}
		clear();
		delete [] _buskets;
		_size = other._size;
		_buskets = new Pair<K, T>* [_size];
		for (size_t i(0); i < _size; ++i) {
			_buskets[i] = nullptr;
		}
		copy(other);
		return *this;
	}

	void clear() {
		Pair<K, T>* tmp = nullptr;
		for (size_t i(0); i < _size; ++i) {
			tmp = _buskets[i];
			while (tmp) {
				auto tmp_next = tmp->next;
				delete tmp;
				tmp = tmp_next;
			}
		}
	}

	void insert(const K& key, const T& value) {
		size_t index = index_hash(key);
		auto tmp = _buskets[index];
		if (!tmp) {
			_buskets[index] = new Pair<K, T>(key, value);
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
				tmp->next = new Pair<K, T>(key, value);
				return;
			}
		}
	}
	void insert_or_assign(const K& key, const T& value) {
		size_t index = index_hash(key);
		auto tmp = _buskets[index];
		if (!tmp) {
			_buskets[index] = new Pair<K, T>(key, value);
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
				tmp->next = new Pair<K, T>(key, value);
				return;
			}
		}
	}
	bool contains(const T& value) {
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
	T* search(const K& key) {
		size_t index = index_hash(key);
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
	bool erase(const K& key) {
		size_t index = index_hash(key);
		auto tmp = _buskets[index];
		if (tmp == nullptr) {
			return false;
		}
		if (tmp->key == key) {
			_buskets[index] = tmp->next;
			delete tmp;
			return true;
		}
		Pair<K, T>* prev = nullptr;
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
	int count(const K& key) {
		size_t index = index_hash(key);
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
		Pair<K, T>* tmp = nullptr;
		for (size_t i(0); i < _size; ++i) {
			tmp = _buskets[i];
			while (tmp) {
				std::cout << tmp->key << " : " << tmp->value << std::endl;
				tmp = tmp->next;
			}
		}
	}
};

size_t pearson_hash(const std::string& str) {

}

bool is_equal(const size_t& first, const size_t& second) {

}




