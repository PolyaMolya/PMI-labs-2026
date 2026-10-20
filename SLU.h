#pragma once
#include <iostream> 
#include "Vector.h"
#include "Matrix.h"

template <typename T>
class SLU :public Matrix<T> {
public:
	SLU(int n) : Matrix<T>(n) {}
	Vector<T> Gauss(const Vector<T>& b) {
		int n = this->GetSize();
		if (b.GetSize() != n) {
				std::cout << "Ошибка, размер вектора b не совпадает с размером матрицы"<<"\n";
				return Vector<T>(0);
		}
		Matrix<T> M = *this; // Kopia Matrici
		Vector<T> x(n);
		for (int i = 0; i < n; i++) {
			x[i] = b[i];
		}
		for (int k = 0; k < n; k++) {
			int number = k; 
			T maxelem = M[k][k];
			if (maxelem < 0) maxelem = -maxelem;

			for (int i = k + 1; i < n; i++) {
				T elem = M[i][k];
				if (elem < 0) elem = -elem;
				if (elem > maxelem) {
					maxelem = elem;
					number = i;
				}
			}
			if (maxelem == 0) {
				std::cout << "Матрица вырождена. Решение не единственно или не существует \n";
				return Vector<T>(0);
			}

			if (number != k) {
				for (int j = 0; j < n; j++) {
					T tmp = M[k][j];
					M[k][j] = M[number][j];
					M[number][j] = tmp;
				}
				T tmp = x[k];
				x[k] = x[number];
				x[number] = tmp;
			}

			T del = M[k][k]; 
			for (int j = 0; j < n; j++) {
				M[k][j] /= del;
			}
			x[k] /= del;

			for (int i = 0; i < n; i++) { 
				if (i != k) {
					T agusha = M[i][k];
					for (int j = 0; j < n; j++) {
						M[i][j] -= agusha * M[k][j];
					}
					x[i] -= agusha * x[k];
				}
			}
		}
		return x;
	}
};