#include <clocale>
#include <iostream>
#include "Vector.h"
#include "Matrix.h"
#include "SLU.h"

int main()
{
    setlocale(LC_ALL, "Russian");
    int n;
    std::cout << "Введите размер матрицы (квадратной):" << "\n";
    std::cin >> n;
    if (n <= 0) {
        std::cout << "Размер должен быть положительным числом \n";
        return 0;
    }

    SLU<double> sys(n);

    std::cout << "Введите (поэлементно) Матрицу размера (" << n << "x" << n << "):" << "\n";
    sys.FillMatrix();
    printf("\n");
    sys.PrintMatrix();
    printf("\n");

    Vector<double> b(n);
    std::cout << "Введите вектор b (" << n << " элементa/ов):" << "\n";
    b.FillVector();
    printf("\n");
    b.PrintVector2();
    printf("\n");

    Vector<double> x = sys.Gauss(b);

    if (x.GetSize() != 0) {
        std::cout << "Ответ:" << "\n";
        x.PrintVector2();
        printf("\n");
    }
}
