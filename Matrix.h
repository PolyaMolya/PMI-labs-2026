#pragma once
#include <iostream>
#include "Vector.h"

template<class T>
class Matrix : public Vector<Vector<T>> {
public:
	Matrix(unsigned int n);
	void SwapLine(int i, int j);
	void PrintMatrix() const;
	void InputMatrix();
};

template<typename T>
Matrix<T>::Matrix(unsigned int n) : Vector<Vector<T>>(n)
{
	for (unsigned int i = 0; i < n; i++)
	{
		(*this)[i] = Vector<T>(n);
	}
}

template<typename T>
void Matrix<T>::PrintMatrix() const
{
	for (unsigned int i = 0; i < this->size; i++)
	{
		this->coordinates[i].PrintVector();
	}
}

template<typename T>
void Matrix<T>::InputMatrix()
{
	for (unsigned int i = 0; i < this->size; i++)
	{
		this->coordinates[i].InputVector();
	}
}

template<typename T>
void Matrix<T>::SwapLine(int i, int j)
{
	if ((*this)[i] == (*this)[j]) { return; }
	Vector<T> tmp = (*this)[i];
	(*this)[i] = (*this)[j];
	(*this)[j] = tmp;
}



