// gauss2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "Matrix.h"
#include "SLAE.h"
#include "vector.h"
int main()
{
    int n=0;
    while (n <= 0) {
        std::cout << "enter size: ";
        std::cin >> n;
    }
    
    Vector<double> b(n);
    SLAE<double> t(n);
    t.set_from_console();
    for (;;) {
        try {
            std::cout << "enter b:\n";
            std::cin >> b;
            std::cout << "ans vector is\n" << t.solve(b) << "\n";
        }
        catch (const char* t) {
            std::cout << t<<"\n";
            break;
        }
    }
    
}
