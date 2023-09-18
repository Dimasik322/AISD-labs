#pragma once

#include <random>
#include <complex>

template <typename T>
class Vector {
private:
	<T>* axes;
	int size;

public:
	Vector() :axes(nullptr), size(0) {};
	Vector(T* axes, int size) :axes(axes), size(size) {};

};