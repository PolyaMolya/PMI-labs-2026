// Laba_Teylor_double.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <cmath>
#include <numbers>
#include <iomanip>

struct x_n {
    int n;
    float* x;
    float* err;
    float* sum;
};
void initialization(int n1, x_n& a) {
    a.n = n1; //кол-во слагаемых
    a.x = (float *)malloc(n1 * sizeof(float)); //массив слагаемых
    a.err = (float*)malloc(n1*sizeof(float)); //погрешности
    a.sum = (float*)malloc(n1*sizeof(float)); //массив частичных сумм
}
void sum_left(x_n& a) {
    for (int i = 1; i < a.n; i++) {
        a.sum[i] = a.sum[i - 1] + a.x[i];
    }
}
void sum_right(x_n& a) {
    //a.sum[a.n - 1] = 0; //?
    a.sum[0] = 0;
    /*for (int i = a.n-2; i>=0; i--) {
        a.sum[i] = a.sum[i + 1] + a.x[i];
    }*/
    for (int i = 1; i < a.n; i++) {
        a.sum[i] = a.sum[i - 1] + a.x[a.n - i-1];
    }
    //a.sum[a.n-1] = a.sum[a.n-2]+a.x[0];
}

void Teylor_sin(x_n& a, float znach, void (*func) (x_n&)) { //получаем массив слагаемых и массив сумм
    a.x[0] = znach;
    a.sum[0] = znach;
    for (int i = 1; i < a.n; i++) {
        a.x[i] = (-1) * znach * znach * a.x[i - 1] / ((2 * (i - 1) + 2) * (2 * (i - 1) + 3));
        //a.sum[i] = a.sum[i - 1] + a.x[i];
    }
    func(a);
}


void Teylor_cos(x_n& a, float znach, void (*func) (x_n&)) { //получаем массив слагаемых и массив сумм
    a.x[0] = 1;
    a.sum[0] = 1;
    for (int i = 1; i < a.n; i++) {
        a.x[i] = (-1) * znach * znach * a.x[i - 1] / ((2 * (i - 1) + 1) * (2 * (i - 1) + 2));
        //a.sum[i] = a.sum[i - 1] + a.x[i];
    }
    func(a);
}
void Teylor_exp(x_n& a, float znach, void (*func) (x_n&)) { //получаем массив слагаемых и массив сумм
    a.x[0] = 1;
    a.sum[0] = 1;
    for (int i = 1; i < a.n; i++) {
        a.x[i] = znach * a.x[i - 1] / i;
        //a.sum[i] = a.sum[i - 1] + a.x[i];
    }
    func(a);
}
void Teylor_ln(x_n& a, float znach, void (*func) (x_n&)) { //получаем массив слагаемых и массив сумм
    a.x[0] = znach;
    a.sum[0] = znach;
    for (int i = 1; i < a.n; i++) {
        a.x[i] = (-1) * znach * (i) * a.x[i - 1] / (i+1);
        //a.sum[i] = a.sum[i - 1] + a.x[i];
    }
    func(a);
}

void err_fill(x_n& a, float znach, float (*func) (float)) {
    for (int i = 0; i < a.n; i++) {
        a.err[i] = abs(func(znach) - a.sum[i]);
    }
}
void clean(x_n& a) {
    free(a.err);
    free(a.sum);
    free(a.x);
}

///
void work ( void (*T) (x_n&, float, void (*func) (x_n&)), x_n& a, x_n& b, float znach, float znach2, float (*F)(float)) {
    T(a, znach, sum_left);
    T(b, znach, sum_right);
    err_fill(a, znach2, F);
    err_fill(b, znach2, F);

}
int main()
{
    
    std::cout << std::fixed << std::setprecision(7);
    x_n a, b; //for sin, cos, exp, ln
    //float x = std::numbers::pi /6;
    float x; int kolv, choose;
    std::cin >> x >> kolv>>choose;  

    initialization(kolv, a);
    initialization(kolv, b);

    switch (choose) {
    case 1:
        work(Teylor_sin, a, b, x, x, sin);
        break;
    case 2:
        work(Teylor_cos, a, b, x, x, cos);
        break;
    case 3:
        work(Teylor_ln, a, b, x, x+1, log);
        break;
    case 4:
        work(Teylor_exp, a, b, x,x, exp);
        break;
    }


    /*Teylor_ln(a, x, sum_left);
    Teylor_ln(b, x, sum_right);


    err_fill(a, x+1, log);
    err_fill(b, x+1, log);*/

    //std::cout << "start print";
    //test output

    //std::cout << "n " << "         sin(x)" << "       err   " << std::endl;


    for (int i = 0; i < a.n - 1; i++) {
        //std::cout << 'S';
        std::cout<< a.err[i] << std::endl;
    }
    //std::cout << 100 << "\t" << a.sum[99] << ' ' << std::endl;

    //std::cout << "n " << "         sin(x)" << "       err   " << std::endl;
    std::cout << std::endl;
    for (int i = 0; i < b.n; i++) {
        std::cout << b.err[i] << std::endl;
    }

    std::cout << std::endl << std::endl;
    clean(a);
    clean(b);
    /*for (int i = 0; i < a.n; i++) {
        std::cout << a.err[i] << ' ';
    }
    std::cout << std::endl << std::endl;*/
    /*for (int i = 0; i < b.n; i++) {
        std::cout << b.sum[i] << ' ';
    }*/
    //std::cout << sin(x*0.5);
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
