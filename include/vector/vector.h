#pragma once

#include <random>
#include <complex>
#include <iostream>

using namespace std;

template <typename T>
class Vector {
private:
	T* axes;
	int size;

public:
	Vector() :axes(nullptr), size(0) {};
	Vector(T* list, int size) : axes(new T[size]), size(size) {
		for (int i(0); i < size; i++) {
			axes[i] = list[i];
		}
	}
	~Vector() {
		delete[] axes;
	}

	T& operator[](const int i) {
		return axes[i];
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
	/*double scalar(const Vector<T>& a, const Vector<T>& b) {
		float scalar = 0;
		if (a.size == b.size) {
			for (int i(0); i < a.size; i++) {
				scalar += (a.axes[i] * b.axes[i]);
			}
		}
		return scalar;
	}*/

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
	

};

template<typename T>
double scalar(Vector<T> a, Vector<T> b) {
	double scalar = 0;
	if (a.get_size() == b.get_size()) {
		for (int i(0); i < a.get_size(); i++) {
			scalar += ((double(a[i])) * (double(b[i])));
		}
	}
	return scalar;
}

template<typename T>
double cos(Vector<T> a, Vector<T> b) {
	return (scalar(a, b) / (double(a.abs()) * double(b.abs())));
}
