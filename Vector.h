#pragma once
#include "Exceptions.h"
#include <iostream>

template<class T>
class Vector {
protected:
	unsigned int size;
	T* coordinates;
public:
	Vector() : size(0), coordinates(nullptr) {};
	Vector(unsigned int size) : size(size), coordinates(new T[size]) {};
	Vector(const Vector& v);
	Vector& operator*= (const Vector& rhs);
	Vector& operator-= (const Vector& rhs);
	bool operator== (const Vector& rhs) const;
	T& operator[] (unsigned int i);
	const T& operator[] (unsigned int i) const;
	Vector operator* (const T& multiplier) const;
	Vector operator/ (const T& divider) const;
	Vector& operator= (const Vector& rhs);
	void InputVector();
	void PrintVector() const;
	~Vector() { delete[] coordinates; }
	unsigned int GetSize() const { return size; }
	T* GetCoor() const { return coordinates; }
};

template<typename T>
Vector<T>::Vector(const Vector& v)
{
	size = v.size;
	coordinates = new T[size];
	for (unsigned int i = 0; i < size; i++)
	{
		coordinates[i] = v.coordinates[i];
	}
}

template<typename T>
void Vector<T>::InputVector()
{
	for (unsigned int i = 0; i < size; i++)
	{
		std::cin >> coordinates[i];
	}
}

template<typename T>
void Vector<T>::PrintVector() const
{
	for (unsigned int i = 0; i < size; i++)
	{
		std::cout << coordinates[i] << ' ';
	}
	std::cout << "\n";
}

template<typename T>
const T& Vector<T>::operator[] (unsigned int i) const
{
	if (i < 0 || i >= size) { throw Exception{ 4, "Index out of range" }; }
	return coordinates[i];
}

template<typename T>
T& Vector<T>::operator[] (unsigned int i)
{
	if (i < 0 || i >= size) { throw Exception{ 4, "Index out of range" }; }
	return coordinates[i];
}

template<typename T>
Vector<T>& Vector<T>::operator= (const Vector<T>& v)
{
	if (this == &v) { return *this; }
	delete[] coordinates;
	size = v.size;
	coordinates = new T[size];
	for (unsigned int i = 0; i < size; i++)
	{
		coordinates[i] = v.coordinates[i];
	}
	return *this;
}
template<typename T>
Vector<T>& Vector<T>::operator*=(const Vector<T>& v)
{
	if (size == v.size)
	{
		for (unsigned int i = 0; i < size; i++)
		{
			coordinates[i] *= v.coordinates[i];
		}
	}
	return *this;
}

template<typename T>
Vector<T>& Vector<T>::operator-=(const Vector<T>& v)
{
	if (size == v.size)
	{
		for (unsigned int i = 0; i < size; i++)
		{
			coordinates[i] -= v.coordinates[i];
		}
	}
	return *this;
}

template<typename T>
Vector<T> Vector<T>::operator/ (const T& divider) const
{
	Vector<T> v = *this;
	for (unsigned int i = 0; i < size; i++)
	{
		v.coordinates[i] /= divider;
	}
	return v;
}

template<typename T>
Vector<T> Vector<T>::operator* (const T& multiplier) const
{
	Vector<T> v = *this;
	for (unsigned int i = 0; i < size; i++)
	{
		v.coordinates[i] *= multiplier;
	}
	return v;
}

template<typename T>
bool Vector<T>::operator== (const Vector& rhs) const
{
	bool diff = false;
	if (size == rhs.size)
	{
		for (unsigned int i = 0; i < size; i++)
		{
			if (rhs[i] != coordinates[i])
			{
				diff = true;
				break;
			}
		}
	}
	else
	{
		diff = true;
	}
	return !diff;
}

