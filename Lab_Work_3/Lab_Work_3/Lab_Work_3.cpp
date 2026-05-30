#include "slau.h"

int main() {
    setlocale(LC_ALL, "RU");

    int choice;

    do {
        int n;
        cout << "Введите размер матрицы: ";
        cin >> n;

        if (n <= 0) {
            cout << "Ошибка: размер матрицы должен быть положительным\n";
            continue;
        }

        SLAU<double> slau(n);

        cout << "Введите матрицу А:\n";
        for (int i = 0; i < n; i++) {
            cout << "Строка " << i + 1 << " (через пробел): ";
            for (int j = 0; j < n; j++) {
                cin >> slau[i][j];
            }
        }

        Vector<double> b(n);
        cout << "Введите вектор правой части b (через пробел):";
        for (int i = 0; i < n; i++) {
            cin >> b[i];
        }

        Vector<double> x = slau.gauss_jordan(b);

        cout << "\nРешение:\n";
        for (int i = 0; i < n; i++) {
            cout << "x" << i + 1 << " = " << x[i] << "\n";
        }

        cout << "1) Решить новую матрицу\n";
        cout << "2) Выйти из программы\n";
        cin >> choice;

        while (choice != 1 && choice != 2) {
            cout << "Ошибка! Введите 1 или 2: ";
            cin >> choice;
        }

        if (choice == 2) {
            cout << "\nПрограмма завершена\n";
        }

    } while (choice != 2);

    return 0;
}