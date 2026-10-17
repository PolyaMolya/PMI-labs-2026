#include <iostream>
#include "SLAU.h"

int main(){
    int n;
    std::cout << "Enter matrix size: ";
    std::cin >> n;
    SLAU<double> slau(n);
    slau.input();

    Vector<double> rightPart(n);
    std::cout << "Enter right part:\n";
    for (int i = 0; i < n; i++){
        std::cin >> rightPart[i];
    }

    Vector<double> result = slau.gauss(rightPart);
    std::cout << "Result:\n";
    for (int i = 0; i < n; i++){
        std::cout << "x" << i + 1 << " = " << result[i] << "\n";
    }
    return 0;
}