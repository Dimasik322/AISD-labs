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
	Vector(T* list, int size) : axes(new T[size]), size(size) {
		for (int i(0); i < size; i++) {
			axes[i] = list[i];
		}
	}
	Vector(Vector& other) : axes(new T[other.size]), size(other.size) {
		for (int i(0); i < size; i++) {
			axes[i] = other.axes[i];
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
	double cos(Vector& other) {
		double cos = ((*this) * other);
		double scalar = double((*this).abs());
		scalar *= double(other.abs());
		return (cos / scalar);
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
		auto tmp = Vector<T>(rhs);
		if (size == rhs.size) {
			for (int i(0); i < size; i++) {
				tmp.axes[i] = axes[i] + rhs.axes[i];
			}
		}
		return tmp;
	}
	Vector operator-(Vector<T>& rhs) {
		auto tmp = Vector<T>(rhs);
		if (size == rhs.size) {
			for (int i(0); i < size; i++) {
				tmp.axes[i] = axes[i] - rhs.axes[i];
			}
		}
		return tmp;
	}
};

template <typename T>
double cos(Vector<T>& a, Vector<T>& b) {
	double cos = (a * b);
	double scalar = double(a.abs());
	scalar *= double(b.abs());
	return ((a * b) / (double(a.abs()) * double(b.abs())));
}

template <typename T>
Vector<T> bis(Vector<T> a, Vector<T> b) {
	auto a_abs = a.abs();
	auto b_abs = b.abs();
	auto x = a_abs / (a_abs + b_abs);
	auto tmp = b - a;
	tmp *= x;
	return tmp + a;
}


