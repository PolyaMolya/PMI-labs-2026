	#pragma once
#include "Exceptions.h"
#include <cmath>
#include <iostream>
#include "Matrix.h"
#include "Vector.h"

template<class T>
class SLU : public Matrix<T> {
public:
	SLU(unsigned int size) : Matrix<T>(size) {};
	void GaussMethod(Vector<T>& right, const T& epsilon );
	void PrintSLU(const Vector<T>& b) const;
	void PrintAnswer(const Matrix<T>& E, const Vector<T>& ans) const;
};

template<typename T>
void SLU<T>::PrintSLU(const Vector<T>& b) const
{
	for (unsigned int i = 0; i < this->size; i++)
	{
		for (unsigned int j = 0; j < this->size; j++)
		{
			std::cout << this->coordinates[i][j] << ' ';
		}
		std::cout << "= " << b[i] << "\n";
	}
	std::cout << "\n" << "\n";
}

template<typename T>
void SLU<T>::PrintAnswer(const Matrix<T>& E, const Vector<T>& ans) const
{
	for (unsigned int i = 0; i < E.GetSize(); i++)
	{
		for (unsigned int j = 0; j < E.GetSize(); j++)
		{
			if (E.GetCoor()[i][j] != 0) { std::cout << 'x' << j + 1 << ' '; }
		}
		std::cout << "= " << ans[i] << '\n';
	}
	std::cout << '\n' << '\n';
}

template<typename T>
void SLU<T>::GaussMethod(Vector<T>& right, const T& epsilon)
{
	unsigned int size = this->size;
	if (right.GetSize() != size)
	{
		throw Exception{ 1, "The sizes of the vector and the coefficient matrix do not match!\n" };
	}
	Matrix<T> tmp = (*this);
	for (unsigned int j = 0; j < size; j++)
	//Идём по столбцам
	{
		unsigned int maxrow = j;
		for (unsigned int i = j; i < size; i++)
		//Идём по строкам
		{
			//Находим строку с самым большим элементом в j-ом столбце
			maxrow = (fabs(tmp[i][j]) > fabs(tmp[maxrow][j])) ? (i) : (maxrow);
		}

		//Проверяем на близость к 0
		if (tmp[maxrow][j] == 0) { throw Exception{ 2, "Zero column, matrix is ​​singular => either there are no solutions, or there are infinitely many of them.\n" }; }
		if (fabs(tmp[maxrow][j]) <= epsilon) { throw Exception{ 3, "For a given system, with a given error bound epsilon, the algorithm cannot find a sufficiently accurate answer.\n" }; }

		//Делим максимальную строку на ведущий элемент
		right[maxrow] = right[maxrow] / tmp[maxrow][j];
		tmp[maxrow] = tmp[maxrow] / tmp[maxrow][j];

		//Ставим строку с  ведущим элементом на диагональ
		tmp.SwapLine(j, maxrow);
		T temp = right[j];
		right[j] = right[maxrow];
		right[maxrow] = temp;

		// Делаем ведущий элемент положительным
		if (tmp[j][j] < 0)
		{
			tmp[j] *= -1;
			right[j] *= -1;
		}
		for (unsigned int i = 0; i < size; i++)
		//Зануляем весь столбец j кроме ведущего элемента
		{
			if (i != j)
			{
				right[i] -= (right[j] * tmp[i][j]);
				tmp[i] -= (tmp[j] * tmp[i][j]);
			}
		}
	}
	this->PrintAnswer(tmp, right);
}

