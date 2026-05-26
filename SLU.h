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
		Matrix<T> M = *this; // Копия матрицы
		Vector<T> x(n); // Копия правой части
		for (int i = 0; i < n; i++) {
			x[i] = b[i];
		}
		for (int k = 0; k < n; k++) {
			int number = k; //номер строки с максимальым элементом
			T maxelem = M[k][k]; // максимальный элемент 
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

			if (number != k) { // Меняем строку k и number местами в матрице M и в правой части x
				for (int j = 0; j < n; j++) {
					T tmp = M[k][j];
					M[k][j] = M[number][j];
					M[number][j] = tmp;
				}
				T tmp = x[k];
				x[k] = x[number];
				x[number] = tmp;
			}

			T del = M[k][k]; // Делим всю СТРОКУ k на M[k][k] (M[k][k] становится = 1)
			for (int j = 0; j < n; j++) {
				M[k][j] /= del;
			}
			x[k] /= del;

			for (int i = 0; i < n; i++) { //зануляем СТОЛБЕЦ k во всех строках, кроме k
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