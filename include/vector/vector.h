#pragma once

#include <random>
#include <complex>
#include <iostream>
#include <cmath>

using namespace std;

template <typename T>
class Vector {
private:
	T* axes;
	int size;

public:
	static inline float accurancy = 0.000001f;
	Vector() {
		int _size = 1 + rand() % 10;
		cout << _size << endl;
		size = _size;
		axes = new T[size];
		for (int i(0); i < size; ++i) {
			axes[i] = rand();
			cout << axes[i] << endl;
		}
	}
	Vector(T* _list, int _size) {
		if (_size <= 0) {
			throw out_of_range("Size of vector cannot be negative or zero");
		}
		else {
			if (_list != nullptr) {
				axes = new T[_size];
				size = _size;
				for (int i(0); i < _size; i++) {
					axes[i] = _list[i];
				}
			}
			else {
				throw out_of_range("Nullptr instead of array ptr");
			}
		}
	}
	Vector(int _size) : size(_size), axes(new T[_size]) {}
	Vector(const Vector& other) : axes(new T[other.size]), size(other.size) {
		for (int i = 0; i < size; ++i) {
			axes[i] = other.axes[i];
		}
	}
	~Vector() {
		delete[] axes;
		axes = nullptr;
		size = 0;
	}

	int get_size() {
		return size;
	}
	T* get_axes() {
		return axes;
	}
	T& operator[](const int i) {
		if (i < 0 || i >= size) {
			throw out_of_range("Index out of size");
		}
		return axes[i];
	}
	void swap(Vector<T>& other) {
		std::swap(this->axes, other.axes);
		std::swap(this->size, other.size);
	}
	double abs() {
		double abs = 0;
		for (int i(0); i < size; i++) {
			abs += pow(axes[i], 2);
		}
		return pow(abs, 0.5);
	}

	Vector<T>& operator+=(const Vector& rhs) {
		if (size == rhs.size) {
			for (int i(0); i < size; i++) {
				axes[i] += rhs.axes[i];
			}
		}
		else {
			throw out_of_range("Different sizes of vectors");
		}
		return *this;
	}
	Vector<T> operator+(Vector<T>& rhs) {
		auto tmp = Vector<T>(*this);
		if (size == rhs.size) {
			for (int i(0); i < size; i++) {
				tmp.axes[i] = axes[i] + rhs.axes[i];
			}
		}
		else {
			throw out_of_range("Different sizes of vectors");
		}
		return tmp;
	}
	Vector<T>& operator-=(const Vector& rhs) {
		if (size == rhs.size) {
			for (int i(0); i < size; i++) {
				axes[i] -= rhs.axes[i];
			}
		}
		else {
			throw out_of_range("Different sizes of vectors");
		}
		return *this;
	}
	Vector<T> operator-(Vector<T>& rhs) {
		auto tmp = Vector<T>(*this);
		if (size == rhs.size) {
			for (int i(0); i < size; i++) {
				tmp.axes[i] = axes[i] - rhs.axes[i];
			}
		}
		else {
			throw out_of_range("Different sizes of vectors");
		}
		return tmp;
	}
	Vector& operator*=(const T& x) {
		for (int i(0); i < size; i++) {
			axes[i] *= x;
		}
		return *this;
	}
	Vector<T> operator*(const T& x) {
		auto tmp = Vector<T>(*this);
		for (int i(0); i < size; i++) {
			tmp.axes[i] = axes[i] * x;
		}
		return tmp;
	}
	Vector<T>& operator/=(const T& x) {
		for (int i(0); i < size; i++) {
			axes[i] /= x;
		}
		return *this;
	}
	Vector<T> operator/(const T& x) {
		auto tmp = Vector<T>(*this);
		for (int i(0); i < size; i++) {
			tmp.axes[i] = axes[i] / x;
		}
		return tmp;
	}
	Vector<T>& operator=(const Vector<T>& rhs) {
		Vector<T> copy(rhs);
		copy.swap(*this);
		return *this;
	}
	bool operator==(Vector<T>& rhs) {
		if (size == rhs.size) {
			for (int i(0); i < size; ++i) {
				if ((axes[i] - rhs.axes[i]) > accurancy) {
					return false;
				}
			}
			return true;
		}
		else {
			return false;
		}
	}
	bool operator!=(Vector<T>& rhs) {
		return !((*this) == rhs);
	}

	T operator*(const Vector<T>& rhs) {
		T sum = 0; 
		if (size == rhs.size) {
			for (int i(0); i < size; i++) {
				cout << sum;
				sum += axes[i] * rhs.axes[i];
			}
		}
		else {
			throw out_of_range("Different sizes of vectors");
		}
		return sum;
	}

};
template<typename T>
std::ostream& operator<<(std::ostream& os, Vector<T> rhs)
{
	for (int i(0); i < rhs.get_size(); ++i) {
		os << rhs[i] << " ";
	}
	return os;
}
template<typename T>
Vector<T> operator*(const T lhs, Vector<T>& rhs) {
	auto tmp = Vector<T>(rhs);
	for (int i(0); i < rhs.get_size(); i++) {
		tmp[i] = lhs * rhs[i];
	}
	return tmp;
}

template<typename T>
double cos(Vector<T>& a, Vector<T>& b) {
	if (a.abs() == 0 || b.abs() == 0) {
		cout << "Vector has zero lenght" << endl;
		return 0;
	}
	return ((a * b) / (double(a.abs()) * double(b.abs())));
}
template<typename T>
Vector<T> bis(Vector<T> a, Vector<T> b) {
	if (a.abs() == 0 || b.abs() == 0) {
		throw invalid_argument("Vector modul cannot be zero");
	}
	auto a_abs = a.abs();
	auto b_abs = b.abs();
	auto x = a_abs / (a_abs + b_abs);
	auto tmp = b - a;
	tmp *= x;
	return tmp + a;
}

//надо разобраться с комплексными числами
