#pragma once

#include <random>
#include <complex>
#include <iostream>
#include <cmath>
#include <stdexcept>

using namespace std;

template <typename T>
class Vector {
private:
	T* axes;
	int size;

public:
	static inline float accurancy = 0.0001f;
	Vector() : size(0), axes(nullptr) {}
	Vector(const int _size, const T& min_value, const T& max_value) {
		size = _size;
		axes = new T[size];
		for (int i(0); i < size; ++i) {
			axes[i] = min_value + (T)(rand()) / RAND_MAX * (max_value - min_value);
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
	T& operator[](const int i) const {
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
			abs += pow(double(axes[i]), 2);
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
		if (x == 0) {
			throw runtime_error("x is zero");
		}
		for (int i(0); i < size; i++) {
			axes[i] /= x;
		}
		return *this;
	}
	Vector<T> operator/(const T& x) {
		if (x == T(0)) {
			throw runtime_error("x is zero");
		}
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
				if ((axes[i].abs() - rhs.abs()) > accurancy) {
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
class Vector<complex<T>>{
private:
	complex<T>* axes;
	int size;

public:
	static inline float accurancy = 0.0001f;
	Vector() : size(0), axes(nullptr) {}	
	Vector(const int _size, const T& min_value, const T& max_value) {
		size = _size;
		axes = new complex<T>[size];
		for (int i(0); i < size; ++i) {
			T re = min_value + (T)(rand()) / RAND_MAX * (max_value - min_value);
			T im = min_value + (T)(rand()) / RAND_MAX * (max_value - min_value);
			axes[i] = complex<T>(re, im);
		}
	}
	Vector(complex<T>* _list, int _size) {
		if (_size <= 0) {
			throw out_of_range("Size of vector cannot be negative or zero");
		}
		else {
			if (_list != nullptr) {
				axes = new complex<T>[_size];
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
	Vector(int _size) : size(_size), axes(new complex<T>[_size]) {}
	Vector(const Vector<complex<T>>& other) : axes(new complex<T>[other.size]), size(other.size) {
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
	complex<T>* get_axes() {
		return axes;
	}
	complex<T>& operator[](const int i) {
		if (i < 0 || i >= size) {
			throw out_of_range("Index out of size");
		}
		return axes[i];
	}
	void swap(Vector<complex<T>>& other) {
		std::swap(this->axes, other.axes);
		std::swap(this->size, other.size);
	}
	double abs() {
		double len = 0;
		for (int i(0); i < size; i++) {
			len += std::abs(axes[i]);
		}
		return pow(len, 0.5);
	}

	Vector<complex<T>>& operator+=(const Vector<complex<T>>& rhs) {
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
	Vector<complex<T>> operator+(Vector<complex<T>>& rhs) {
		auto tmp = Vector<complex<T>>(*this);
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
	Vector<complex<T>>& operator-=(const Vector<complex<T>>& rhs) {
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
	Vector<complex<T>> operator-(Vector<complex<T>>& rhs) {
		auto tmp = Vector<complex<T>>(*this);
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
	Vector<complex<T>>& operator*=(const complex<T>& x) {
		for (int i(0); i < size; i++) {
			axes[i] *= x;
		}
		return *this;
	}
	Vector<complex<T>> operator*(const complex<T>& x) {
		auto tmp = Vector<complex<T>>(*this);
		for (int i(0); i < size; i++) {
			tmp.axes[i] = axes[i] * x;
		}
		return tmp;
	}
	Vector<complex<T>>& operator/=(const complex<T>& x) {
		for (int i(0); i < size; i++) {
			axes[i] /= x;
		}
		return *this;
	}
	Vector<complex<T>> operator/(const complex<T>& x) {
		auto tmp = Vector<complex<T>>(*this);
		for (int i(0); i < size; i++) {
			tmp.axes[i] = axes[i] / x;
		}
		return tmp;
	}
	Vector<complex<T>>& operator=(const Vector<complex<T>>& rhs) {
		Vector<complex<T>> copy(rhs);
		copy.swap(*this);
		return *this;
	}
	bool operator==(Vector<complex<T>>& rhs) {
		if (size == rhs.size) {
			for (int i(0); i < size; ++i) {
				auto tmp = axes[i] - rhs.axes[i];
				if (std::abs(tmp) > accurancy){
					return false;
				}
			}
			return true;
		}
		else {
			return false;
		}
	}
	bool operator!=(Vector<complex<T>>& rhs) {
		return !((*this) == rhs);
	}

	complex<T> operator*(const Vector<complex<T>>& rhs) {
		complex<T> sum = 0;
		if (size == rhs.size) {
			for (int i(0); i < size; i++) {
				sum += (axes[i] * complex<T>(rhs.axes[i].real(), rhs.axes[i].imag() * (-1)));
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
complex<double> cos(Vector<complex<T>>& a, Vector<complex<T>>& b) {
	if (a.abs() == 0 || b.abs() == 0) {
		cout << "Vector has zero lenght" << endl;
		return 0;
	}
	return (double(a * b) / (double(a.abs()) * double(b.abs())));
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