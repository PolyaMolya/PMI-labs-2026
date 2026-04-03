// laba2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <stdio.h>
#include "Func.h"
#include <math.h>

int main()
{
    setlocale(LC_ALL, "Russian");
    setlocale(LC_NUMERIC, "C");

    struct Xn ryad;
    int size;
    float x;
    int choice;
    float (*func)(float prev, float x, int n);
    float (*f)(float);

    printf("Введите количество членов ряда:\n");
    scanf_s("%d", &size);
    Init(&ryad, size);
    printf("Введите x:\n");
    scanf_s("%f", &x);
    printf("Выберите функцию:\n");
    printf("1 - exp(x)\n");
    printf("2 - sin(x)\n");
    printf("3 - cos(x)\n");
    printf("4 - ln(1+x)\n");
    scanf_s("%d", &choice);

    if (choice == 1) {
        InitStateCosandExp(&ryad);
        func = Exponenta;
        f = expf;
    }
    else if (choice == 2) {
        InitStateSinandLog(&ryad, x);
        func = Sinus;
        f = sinf;
    }
    else if (choice == 3) {
        InitStateCosandExp(&ryad);
        func = Cosinus;
        f = cosf;
    }
    else if (choice == 4) {
        InitStateSinandLog(&ryad, x);
        func = Logarifm;
        f = log1pf;
    }
    else {
        printf("Неверный выбор\n");
        Free(&ryad);
        return 0;
    }

    Fill(&ryad, x, func);
    PrintArr(&ryad);
    SumForward(&ryad, x, f);
    SumBack(&ryad, x, f);
    PrintResult(&ryad);
    Free(&ryad);
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
