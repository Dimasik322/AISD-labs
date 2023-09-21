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
	Vector() :axes(nullptr), size(0) {};
	Vector(T* _list, int _size) {
		if (_size < 0) {
			cout << "The dimension of a verctor cannot be negative" << endl;
			axes = nullptr;
			size = 0;
		}
		else {
			axes = new T[_size];
			size = _size;
			for (int i(0); i < _size; i++) {
				axes[i] = _list[i];
			}
		}
	}
	Vector(Vector& other) : axes(new T[other.size]), size(other.size) {
		for (int i(0); i < size; i++) {
			axes[i] = other.axes[i];
		}
	}
	~Vector() {
		delete[] axes;
		axes = nullptr;
	}

	int get_size() {
		return size;
	}
	void set_value(const int index, const T& value) {
		for (int i(0); i < size; i++) {
			if (i == index) {
				axes[i] = value;
			}
		}
	}
	double abs() {
		double abs = 0;
		for (int i(0); i < size; i++) {
			abs += pow(axes[i], 2);
		}
		return pow(abs, 0.5);
	}
	T& operator[](const int i) {
		if (i < 0 || i >= size) {
			cout << "Index out of range" << endl;
			return axes[0];
		}
		return axes[i];
	}
	Vector& operator=(const Vector& rhs) {
		if (this != &rhs) {
			delete[] axes;
			size = rhs.size;
			axes = new T[size];
			for (int i(0); i < size; i++) {
				axes[i] = rhs.axes[i];
			}
		}
		return *this;
	}
	Vector& operator+=(const Vector& rhs) {
		if (size == rhs.size) {
			for (int i(0); i < size; i++) {
				axes[i] += rhs.axes[i];
			}
		}
		return *this;	
	}
	Vector& operator-=(const Vector& rhs) {
		if (size == rhs.size) {
			for (int i(0); i < size; i++) {
				axes[i] -= rhs.axes[i];
			}
		}
		return *this;
	}
	Vector& operator*=(const T& x) {
		for (int i(0); i < size; i++) {
			axes[i] *= x;
		}
		return *this;
	}
	Vector& operator/=(const T& x) {
		for (int i(0); i < size; i++) {
			axes[i] /= x;
		}
		return *this;
	}
	double operator*(const Vector& rhs) {
		double sum = 0;
		if (size == rhs.size) {
			for (int i(0); i < size; i++) {
				sum += double(axes[i]) * double(rhs.axes[i]);
			}
		}
		return sum;
	}
	Vector operator+(Vector<T>& rhs) {
		auto tmp = Vector<T>(*this);
		if (size == rhs.size) {
			for (int i(0); i < size; i++) {
				tmp.axes[i] = axes[i] + rhs.axes[i];
			}
		}
		return tmp;
	}
	Vector operator-(Vector<T>& rhs) {
		auto tmp = Vector<T>(*this);
		if (size == rhs.size) {
			for (int i(0); i < size; i++) {
				tmp.axes[i] = axes[i] - rhs.axes[i];
			}
		}
		return tmp;
	}
	bool operator==(Vector<T>& rhs) {
		if (size == rhs.size) {
			for (int i(0); i < size; ++i) {
				if (axes[i] != rhs.axes[i]) {
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
};

template<typename T>
double cos(Vector<T>& a, Vector<T>& b) {
	if (a.abs()==0 || b.abs()==0) {
		cout << "Vector has zero lenght" << endl;
		return 0;
	}
	return ((a * b) / (double(a.abs()) * double(b.abs())));
}

template<typename T>
Vector<T> bis(Vector<T> a, Vector<T> b) {
	if (a.abs()==0 || b.abs()==0) {
		cout << "Vector has zero lenght" << endl;
		//auto tmp = Vector<T>({0}, 0);
		return Vector<T>({ 0 }, 0);
	}
	auto a_abs = a.abs();
	auto b_abs = b.abs();
	auto x = a_abs / (a_abs + b_abs);
	auto tmp = b - a;
	tmp *= x;
	return tmp + a;
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
Vector<complex<T>> operator*(const T lhs, Vector<complex<T>>& rhs) {
	auto tmp = Vector<complex<T>>(rhs);
	for (int i(0); i < rhs.get_size(); i++) {
		tmp[i] *= lhs;
	}
	return tmp;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, Vector<T> rhs)
{
	for (int i(0); i < rhs.get_size(); ++i) {
		os << rhs[i] << " ";
	}
	return os;
}


//надо переделать под комплексные: оператор скалярного произв, модуль; разобраться с исключениями и генератором случайных чисел для конструктора по умолч;
