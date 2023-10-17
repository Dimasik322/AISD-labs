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
	Vector(): size(0), axes(nullptr){
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
				if ((axes[i] - rhs.axes[i]) == 0) {
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


template<>
class Vector<int> {
private:
	int* axes;
	int size;

public:
	static inline float accurancy = 0.000001f;
	Vector() {
		int _size = 1 + (int)(rand()) / RAND_MAX * 7;
		cout << _size << endl;
		size = _size;
		axes = new int[size];
		for (int i(0); i < size; ++i) {
			axes[i] = (int)(rand()) / RAND_MAX * 127;
			cout << axes[i] << endl;
		}
	}
	Vector(int* _list, int _size) {
		if (_size <= 0) {
			throw out_of_range("Size of vector cannot be negative or zero");
		}
		else {
			if (_list != nullptr) {
				axes = new int[_size];
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
	Vector(int _size) : size(_size), axes(new int[_size]) {}
	Vector(const Vector& other) : axes(new int[other.size]), size(other.size) {
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
	int* get_axes() {
		return axes;
	}
	int& operator[](const int i) {
		if (i < 0 || i >= size) {
			throw out_of_range("Index out of size");
		}
		return axes[i];
	}
	void swap(Vector<int>& other) {
		std::swap(this->axes, other.axes);
		std::swap(this->size, other.size);
	}
	float abs() {
		float abs = 0;
		for (int i(0); i < size; i++) {
			abs += pow(float(axes[i]), 2);
		}
		return pow(abs, 0.5);
	}

	Vector<int>& operator+=(const Vector& rhs) {
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
	Vector<int> operator+(Vector<int>& rhs) {
		auto tmp = Vector<int>(*this);
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
	Vector<int>& operator-=(const Vector<int>& rhs) {
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
	Vector<int> operator-(Vector<int>& rhs) {
		auto tmp = Vector<int>(*this);
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
	Vector<int>& operator*=(const int& x) {
		for (int i(0); i < size; i++) {
			axes[i] *= x;
		}
		return *this;
	}
	Vector<int> operator*(const int& x) {
		auto tmp = Vector<int>(*this);
		for (int i(0); i < size; i++) {
			tmp.axes[i] = axes[i] * x;
		}
		return tmp;
	}
	Vector<int>& operator/=(const int& x) {
		for (int i(0); i < size; i++) {
			axes[i] /= x;
		}
		return *this;
	}
	Vector<int> operator/(const int& x) {
		auto tmp = Vector<int>(*this);
		for (int i(0); i < size; i++) {
			tmp.axes[i] = axes[i] / x;
		}
		return tmp;
	}
	Vector<int>& operator=(const Vector<int>& rhs) {
		Vector<int> copy(rhs);
		copy.swap(*this);
		return *this;
	}
	bool operator==(Vector<int>& rhs) {
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
	bool operator!=(Vector<int>& rhs) {
		return !((*this) == rhs);
	}

	int operator*(const Vector<int>& rhs) {
		int sum = 0;
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
template <>
class Vector<float> {
private:
	float* axes;
	int size;

public:
	static inline float accurancy = 0.000001f;
	Vector() {
		int _size = 1 + (int)(rand()) / RAND_MAX * 7;
		cout << _size << endl;
		size = _size;
		axes = new float[size];
		for (int i(0); i < size; ++i) {
			axes[i] = (float)(rand()) / RAND_MAX * 127;
			cout << axes[i] << endl;
		}
	}
	Vector(float* _list, int _size) {
		if (_size <= 0) {
			throw out_of_range("Size of vector cannot be negative or zero");
		}
		else {
			if (_list != nullptr) {
				axes = new float[_size];
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
	Vector(int _size) : size(_size), axes(new float[_size]) {}
	Vector(const Vector& other) : axes(new float[other.size]), size(other.size) {
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
	float* get_axes() {
		return axes;
	}
	float& operator[](const int i) {
		if (i < 0 || i >= size) {
			throw out_of_range("Index out of size");
		}
		return axes[i];
	}
	void swap(Vector<float>& other) {
		std::swap(this->axes, other.axes);
		std::swap(this->size, other.size);
	}
	float abs() {
		float abs = 0;
		for (int i(0); i < size; i++) {
			abs += pow(float(axes[i]), 2);
		}
		return float(pow(abs, 0.5));
	}

	Vector<float>& operator+=(const Vector& rhs) {
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
	Vector<float> operator+(Vector<float>& rhs) {
		auto tmp = Vector<float>(*this);
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
	Vector<float>& operator-=(const Vector<float>& rhs) {
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
	Vector<float> operator-(Vector<float>& rhs) {
		auto tmp = Vector<float>(*this);
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
	Vector<float>& operator*=(const float& x) {
		for (int i(0); i < size; i++) {
			axes[i] *= x;
		}
		return *this;
	}
	Vector<float> operator*(const float& x) {
		auto tmp = Vector<float>(*this);
		for (int i(0); i < size; i++) {
			tmp.axes[i] = axes[i] * x;
		}
		return tmp;
	}
	Vector<float>& operator/=(const float& x) {
		for (int i(0); i < size; i++) {
			axes[i] /= x;
		}
		return *this;
	}
	Vector<float> operator/(const float& x) {
		auto tmp = Vector<float>(*this);
		for (int i(0); i < size; i++) {
			tmp.axes[i] = axes[i] / x;
		}
		return tmp;
	}
	Vector<float>& operator=(const Vector<float>& rhs) {
		Vector<float> copy(rhs);
		copy.swap(*this);
		return *this;
	}
	bool operator==(Vector<float>& rhs) {
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
	bool operator!=(Vector<float>& rhs) {
		return !((*this) == rhs);
	}

	float operator*(const Vector<float>& rhs) {
		float sum = 0;
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
template <>
class Vector<double> {
private:
	double* axes;
	int size;

public:
	static inline float accurancy = 0.000001f;
	Vector() {
		int _size = 1 + (int)(rand()) / RAND_MAX * 7;
		cout << _size << endl;
		size = _size;
		axes = new double[size];
		for (int i(0); i < size; ++i) {
			axes[i] = (double)(rand()) / RAND_MAX * 127;
			cout << axes[i] << endl;
		}
	}
	Vector(double* _list, int _size) {
		if (_size <= 0) {
			throw out_of_range("Size of vector cannot be negative or zero");
		}
		else {
			if (_list != nullptr) {
				axes = new double[_size];
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
	Vector(int _size) : size(_size), axes(new double[_size]) {}
	Vector(const Vector<double>& other) : axes(new double[other.size]), size(other.size) {
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
	double* get_axes() {
		return axes;
	}
	double& operator[](const int i) {
		if (i < 0 || i >= size) {
			throw out_of_range("Index out of size");
		}
		return axes[i];
	}
	void swap(Vector<double>& other) {
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

	Vector<double>& operator+=(const Vector<double>& rhs) {
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
	Vector<double> operator+(Vector<double>& rhs) {
		auto tmp = Vector<double>(*this);
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
	Vector<double>& operator-=(const Vector<double>& rhs) {
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
	Vector<double> operator-(Vector<double>& rhs) {
		auto tmp = Vector<double>(*this);
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
	Vector<double>& operator*=(const double& x) {
		for (int i(0); i < size; i++) {
			axes[i] *= x;
		}
		return *this;
	}
	Vector<double> operator*(const double& x) {
		auto tmp = Vector<double>(*this);
		for (int i(0); i < size; i++) {
			tmp.axes[i] = axes[i] * x;
		}
		return tmp;
	}
	Vector<double>& operator/=(const double& x) {
		for (int i(0); i < size; i++) {
			axes[i] /= x;
		}
		return *this;
	}
	Vector<double> operator/(const double& x) {
		auto tmp = Vector<double>(*this);
		for (int i(0); i < size; i++) {
			tmp.axes[i] = axes[i] / x;
		}
		return tmp;
	}
	Vector<double>& operator=(const Vector<double>& rhs) {
		Vector<double> copy(rhs);
		copy.swap(*this);
		return *this;
	}
	bool operator==(Vector<double>& rhs) {
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
	bool operator!=(Vector<double>& rhs) {
		return !((*this) == rhs);
	}

	double operator*(const Vector<double>& rhs) {
		double sum = 0;
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


template <>
class Vector<complex<float>>{
private:
	complex<float>* axes;
	int size;

public:
	static inline float accurancy = 0.000001f;
	Vector() {
		int _size = 1 + (int)(rand()) / RAND_MAX * 7;
		cout << _size << endl;
		size = _size;
		axes = new complex<float>[size];
		for (int i(0); i < size; ++i) {
			float re = (float)(rand()) / RAND_MAX * 127;
			float im = (float)(rand()) / RAND_MAX * 127;
			axes[i] = complex<float>(re, im);
			//cout << axes[i] << endl;
		}
	}
	Vector(complex<float>* _list, int _size) {
		if (_size <= 0) {
			throw out_of_range("Size of vector cannot be negative or zero");
		}
		else {
			if (_list != nullptr) {
				axes = new complex<float>[_size];
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
	Vector(int _size) : size(_size), axes(new complex<float>[_size]) {}
	Vector(const Vector& other) : axes(new complex<float>[other.size]), size(other.size) {
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
	complex<float>* get_axes() {
		return axes;
	}
	complex<float>& operator[](const int i) {
		if (i < 0 || i >= size) {
			throw out_of_range("Index out of size");
		}
		return axes[i];
	}
	void swap(Vector<complex<float>>& other) {
		std::swap(this->axes, other.axes);
		std::swap(this->size, other.size);
	}
	/*float abs() {
		complex<float> abs = 0;
		for (int i(0); i < size; i++) {
			abs += complex<float>((pow(axes[i], 2)));
		}
		return sqrt(abs);
	}*/

	Vector<complex<float>>& operator+=(const Vector<complex<float>>& rhs) {
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
	Vector<complex<float>> operator+(Vector<complex<float>>& rhs) {
		auto tmp = Vector<complex<float>>(*this);
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
	Vector<complex<float>>& operator-=(const Vector<complex<float>>& rhs) {
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
	Vector<complex<float>> operator-(Vector<complex<float>>& rhs) {
		auto tmp = Vector<complex<float>>(*this);
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
	Vector<complex<float>>& operator*=(const float& x) {
		for (int i(0); i < size; i++) {
			axes[i] *= x;
		}
		return *this;
	}
	Vector<complex<float>> operator*(const float& x) {
		auto tmp = Vector<complex<float>>(*this);
		for (int i(0); i < size; i++) {
			tmp.axes[i] = axes[i] * x;
		}
		return tmp;
	}
	Vector<complex<float>>& operator/=(const float& x) {
		for (int i(0); i < size; i++) {
			axes[i] /= x;
		}
		return *this;
	}
	Vector<complex<float>> operator/(const float& x) {
		auto tmp = Vector<complex<float>>(*this);
		for (int i(0); i < size; i++) {
			tmp.axes[i] = axes[i] / x;
		}
		return tmp;
	}
	Vector<complex<float>>& operator=(const Vector<complex<float>>& rhs) {
		Vector<complex<float>> copy(rhs);
		copy.swap(*this);
		return *this;
	}
	bool operator==(Vector<complex<float>>& rhs) {
		if (size == rhs.size) {
			for (int i(0); i < size; ++i) {
				if (((axes[i] - rhs.axes[i]).real() < accurancy) && ((axes[i] - rhs.axes[i]).imag() < accurancy)){
					return false;
				}
			}
			return true;
		}
		else {
			return false;
		}
	}
	bool operator!=(Vector<complex<float>>& rhs) {
		return !((*this) == rhs);
	}

	complex<float> operator*(const Vector<complex<float>>& rhs) {
		complex<float> sum = 0;
		if (size == rhs.size) {
			for (int i(0); i < size; i++) {
				sum += (axes[i] * complex<float>(rhs.axes[i].real(), rhs.axes[i].imag() * (-1)));
			}
		}
		else {
			throw out_of_range("Different sizes of vectors");
		}
		return sum;
	}
};
template <>
class Vector<complex<double>> {
private:
	complex<double>* axes;
	int size;

public:
	static inline float accurancy = 0.000001f;
	Vector() {
		int _size = 1 + (int)(rand()) / RAND_MAX * 7;
		cout << _size << endl;
		size = _size;
		axes = new complex<double>[size];
		for (int i(0); i < size; ++i) {
			double re = (double)(rand()) / RAND_MAX * 127;
			double im = (double)(rand()) / RAND_MAX * 127;
			axes[i] = complex<double>(re, im);
			//cout << axes[i] << endl;
		}
	}
	Vector(complex<double>* _list, int _size) {
		if (_size <= 0) {
			throw out_of_range("Size of vector cannot be negative or zero");
		}
		else {
			if (_list != nullptr) {
				axes = new complex<double>[_size];
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
	Vector(int _size) : size(_size), axes(new complex<double>[_size]) {}
	Vector(const Vector& other) : axes(new complex<double>[other.size]), size(other.size) {
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
	complex<double>* get_axes() {
		return axes;
	}
	complex<double>& operator[](const int i) {
		if (i < 0 || i >= size) {
			throw out_of_range("Index out of size");
		}
		return axes[i];
	}
	void swap(Vector<complex<double>>& other) {
		std::swap(this->axes, other.axes);
		std::swap(this->size, other.size);
	}
	/*float abs() {
		complex<float> abs = 0;
		for (int i(0); i < size; i++) {
			abs += complex<float>((pow(axes[i], 2)));
		}
		return sqrt(abs);
	}*/

	Vector<complex<double>>& operator+=(const Vector<complex<double>>& rhs) {
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
	Vector<complex<double>> operator+(Vector<complex<double>>& rhs) {
		auto tmp = Vector<complex<double>>(*this);
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
	Vector<complex<double>>& operator-=(const Vector<complex<double>>& rhs) {
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
	Vector<complex<double>> operator-(Vector<complex<double>>& rhs) {
		auto tmp = Vector<complex<double>>(*this);
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
	Vector<complex<double>>& operator*=(const double& x) {
		for (int i(0); i < size; i++) {
			axes[i] *= x;
		}
		return *this;
	}
	Vector<complex<double>> operator*(const double& x) {
		auto tmp = Vector<complex<double>>(*this);
		for (int i(0); i < size; i++) {
			tmp.axes[i] = axes[i] * x;
		}
		return tmp;
	}
	Vector<complex<double>>& operator/=(const double& x) {
		for (int i(0); i < size; i++) {
			axes[i] /= x;
		}
		return *this;
	}
	Vector<complex<double>> operator/(const double& x) {
		auto tmp = Vector<complex<double>>(*this);
		for (int i(0); i < size; i++) {
			tmp.axes[i] = axes[i] / x;
		}
		return tmp;
	}
	Vector<complex<double>>& operator=(const Vector<complex<double>>& rhs) {
		Vector<complex<double>> copy(rhs);
		copy.swap(*this);
		return *this;
	}
	bool operator==(Vector<complex<double>>& rhs) {
		if (size == rhs.size) {
			for (int i(0); i < size; ++i) {
				if (((axes[i] - rhs.axes[i]).real() < accurancy) && ((axes[i] - rhs.axes[i]).imag() < accurancy)) {
					return false;
				}
			}
			return true;
		}
		else {
			return false;
		}
	}
	bool operator!=(Vector<complex<double>>& rhs) {
		return !((*this) == rhs);
	}

	complex<double> operator*(const Vector<complex<double>>& rhs) {
		complex<double> sum = 0;
		if (size == rhs.size) {
			for (int i(0); i < size; i++) {
				sum += (axes[i] * complex<double>(rhs.axes[i].real(), rhs.axes[i].imag() * (-1)));
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

// доделать в комплексных abs(), cos(), bis()