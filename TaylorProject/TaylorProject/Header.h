#pragma once

#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>

struct Series {
    std::vector<double> values;      // Массив значений членов ряда 
    std::vector<double> sums;        // Массив сумм
    std::vector<double> errors;      // Массив ошибок 
    double exactValue;              // Точное значение функции 
};

Series calculateEx(double x, int maxZnach);
Series calculateSin(double x, int maxZnach);
Series calculateCos(double x, int maxZnach);
Series calculateLn(double x, int maxZnach);
Series calculateSumForward(const Series& inputSeries, int maxZnach);
Series calculateSumBackward(const Series& inputSeries, int maxZnach);
void printResults(const Series& series, int maxTerms);

