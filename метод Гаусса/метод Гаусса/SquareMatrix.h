#pragma once

#include <iostream>
#include "Vector.h"

//квадратная матрица
template<typename T>
class SquareMatrix{
protected:
    Vector<Vector<T>> matrix;
    int n;
public:
    SquareMatrix(int size = 0) : n(size){
        matrix.resize(n);
        for (int i = 0; i < n; i++){
            matrix[i].resize(n);
        }
    }

    int size() const{ return n;}

    Vector<T>& operator[](int i) {return matrix[i];}
    const Vector<T>& operator[](int i) const { return matrix[i];}

    void input(){
        std::cout << "Enter matrix " << n << "x" << n << ":\n";
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                std::cin >> matrix[i][j];
            }
        }
    }

    void output() const{
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                std::cout << matrix[i][j] << " ";
            }
            std::cout << "\n";
        }
    }

    //для обмена строк
    void swapRows(int row1, int row2){
        if (row1 == row2) return;
        for (int j = 0; j < n; j++){
            T temp = matrix[row1][j];
            matrix[row1][j] = matrix[row2][j];
            matrix[row2][j] = temp;
        }
    }
};

