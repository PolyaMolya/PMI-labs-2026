#pragma once
#include "Matrix.h"
#include <iostream>
template<typename T>
class SLAE :public Matrix<T> {

public:

	//построить по матрице
	SLAE(Matrix<T> t): Matrix<T>(t) {}
	SLAE(int n) :Matrix<T>(n) {}
	//метод Гаусса
	Vector<T> solve(const Vector<T> &num) {
		if (num.size() != this->size()) {
			throw "Err: scale of num don`t mathes with scale of matrix";
		}
		Vector<T> c(num);
		int n = this->size();
		Matrix<T> b (*this);
		
		//go forward, step type
		for (int i = 0;i < n; i++) {
			T t = b[i][i];
			if (t == 0) { 
				bool fl = 1;
				for (int j = i + 1; j < n; ++j) {
					if (b[j][i] != 0) {
						b[i].swap(b[j]);
						T tmp = c[i];
						c[i] = c[j];
						c[j] = tmp;
						fl = 0;
						break;
					}
				}
				if (fl) {
					throw "Err: det(A) = 0";
				}
			}
			t = b[i][i];
			b[i] *= (1.0 / t);
			c[i] /=t;
			
			//go down
			for (int j = i + 1; j < n; j++) {
				c[j] -= c[i] * b[j][i];
				b[j] -= (b[i] * b[j][i]);
			}
			//b.print();
		}	
		//go back
		for (int i = n - 1; i > 0; --i) {
			//go up
			for (int j = i - 1; j >= 0; --j) {
				c[j] -= c[i] * b[j][i];
				b[j] -= b[i]*b[j][i];
			}
		}
		return c;
	}
};