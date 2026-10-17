#pragma once

#include <cmath>
#include "SquareMatrix.h"

//класс СЛАУ наследник квадратной матрицы
template<typename T>
class SLAU : public SquareMatrix<T>{
public:
    SLAU(int size) : SquareMatrix<T>(size) {}

    //метод гаусса
    Vector<T> gauss(Vector<T>& rightPart){
        int n = this->n;

        //прямой ход
        for (int k = 0; k < n - 1; k++){
            //Выбор ведущего элемента
            int maxRow = k;
            T maxVal = std::abs(this->matrix[k][k]);
            for (int i = k + 1; i < n; i++) {
                if (std::abs(this->matrix[i][k]) > maxVal){
                    maxVal = std::abs(this->matrix[i][k]);
                    maxRow = i;
                }
            }
            //swap строк
            if (maxRow != k){
                this->swapRows(k, maxRow);
                T temp = rightPart[k];
                rightPart[k] = rightPart[maxRow];
                rightPart[maxRow] = temp;
            }

            //исключение
            for (int i = k + 1; i < n; i++) {
                T factor = this->matrix[i][k] / this->matrix[k][k];
                for (int j = k; j < n; j++) {
                    this->matrix[i][j] -= factor * this->matrix[k][j];
                }
                rightPart[i] -= factor * rightPart[k];
            }
        }

        //обрвтный ход
        Vector<T> result(n);
        for (int i = n - 1; i >= 0; i--){
            T sum = 0;
            for (int j = i + 1; j < n; j++) {
                sum += this->matrix[i][j] * result[j];
            }
            result[i] = (rightPart[i] - sum) / this->matrix[i][i];
        }

        return result;
    }
};
