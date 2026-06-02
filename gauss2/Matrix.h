#pragma once
#include "vector.h"
#include <initializer_list>

template <typename T>
class Matrix:public Vector<Vector<T>> {

public:
	// размер и значение
	Matrix(int n, T k) : Vector<Vector<T>>(n, Vector<T>(n, k)) {}
	// размер
	Matrix(int n) : Vector<Vector<T>>(n, Vector<T>(n)) {}
	
	int size() {
		return this->n;
	}
	void set_from_console() {
		std::cout << "enter elements:\n";
		for (int i = 0;i < this->n;i++) {
			std::cin >> this->a[i];
		}
		
	}
	Vector<T>&operator[](int x) {return this->a[x];}
	void print() {
		this->a.print();
	}
};