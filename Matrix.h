#pragma once
#include <iostream> 
#include "Vector.h"

template <typename T>
class Matrix :public Vector<Vector<T>> {
public:
	Matrix(int n) :Vector<Vector<T>>(n, Vector<T>(n, T())) {};
	int GetSize() const {
		return this->size;
	}
	void PrintMatrix() {
		for (int i = 0; i < this->size; i++) {
			this->vec[i].PrintVector();
			std::cout << "\n";
		}
	}
	void FillMatrix() {
		for (int i = 0; i < this->size; i++) {
			this->vec[i].FillVector();
		}
	}

};