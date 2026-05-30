#pragma once
#include "vector.h"
#include <initializer_list>

template <typename T>
class Matrix {
private:
	int n;
protected:
	Vector<Vector<T>> a;
public:
	//размер и значение
	Matrix(int n, int k) {
		a = Vector<Vector<T>>(n, Vector<T>(n, k));
		this->n = n;
	}
	//размер
	Matrix(int n) {
		a = Vector<Vector<T>>(n, Vector<T>(n));
		this->n = n;
	}
	//initializer list
	Matrix(std::initializer_list<std::initializer_list<T>> t) {
		this->n = t.size();
		a = Vector<Vector<T>>(n, Vector<T>(n));
		int ii = 0;
		int ij = 0;
		for (std::initializer_list<T> i: t) {
			this->m = i.size();
			for (T j : i) {
				a[ii][ij] = j;
				ij++;
			}
			ii++;
		}
	}
	//конструктор от вектора векторов
	Matrix(Vector<Vector<T>>& t) {
		this->n = t.size();
		if (t[0].size() != n) {
			throw "index error";
		}
		a = t;
	}
	int size() {
		return n;
	}
	void set_from_console() {
		std::cout << "enter elements:\n";
		std::cin >> a;
	}
	Vector<T>&operator[](int x) {return a[x];}
	void print() {
		a.print();
	}
};