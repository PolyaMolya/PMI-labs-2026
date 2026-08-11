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

    int k;
    std::cout << "Введите количество правых частей"<<"\n";
    std::cin >> k;
    if (k <= 0) {
        std::cout << "Количество должно быть положительным.\n";
        return 0;
    }

    printf("\n");

    for (int t = 0; t < k; t++) {
        Vector<double> b(n);
        std::cout << "Введите вектор b" << t + 1 << " (" << n << " элементa/ов):"<<"\n";
        b.FillVector();

        Vector<double> x = sys.Gauss(b);

        if (x.GetSize() == 0) {
            std::cout << "Для вектора b" << t + 1 << " решение не найдено.\n\n";
            continue;
        }

        std::cout << "Решение " << t + 1 << ":\n";
        x.PrintVector2();
        printf("\n");
    }
}
