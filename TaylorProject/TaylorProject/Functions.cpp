#include "Header.h"

Series calculateEx(double x, int maxZnach) {
    Series res;

    res.exactValue = exp(x);

    res.values.resize(maxZnach);
    res.sums.resize(maxZnach);
    res.errors.resize(maxZnach);

    res.values[0] = 1.0;
    res.sums[0] = res.values[0];
    res.errors[0] = abs(res.sums[0] - res.exactValue);

    // X {n+1} = X_n * (x / (n+1))
    for (int i = 1; i < maxZnach; i++) {
        res.values[i] = res.values[i - 1] * (x / i);
    }
    return res;
}


Series calculateSin(double x, int maxZnach) {
    Series res;

    res.exactValue = sin(x);
    res.values.resize(maxZnach);
    res.sums.resize(maxZnach);
    res.errors.resize(maxZnach);

    res.values[0] = x;
    res.sums[0] = res.values[0];
    res.errors[0] = abs(res.sums[0] - res.exactValue);

    // X {n+1} = -X_n * (x^2 / ((2n+2)(2n+3)))
    for (int i = 1; i < maxZnach; i++) {
        double factor = (x * x) / ((2 * i) * (2 * i + 1));
        res.values[i] = -res.values[i - 1] * factor;
    }
    return res;
}


Series calculateCos(double x, int maxZnach) {
    Series res;

    res.exactValue = cos(x);

    res.values.resize(maxZnach);
    res.sums.resize(maxZnach);
    res.errors.resize(maxZnach);

    res.values[0] = 1.0;
    res.sums[0] = res.values[0];
    res.errors[0] = abs(res.sums[0] - res.exactValue);

    // X {n+1} = -X_n * (x^2 / ((2n+1)(2n+2)))
    for (int i = 1; i < maxZnach; i++) {
        double factor = (x * x) / ((2 * i - 1) * (2 * i));
        res.values[i] = -res.values[i - 1] * factor;
    }
    return res;
}


Series calculateLn(double x, int maxZnach) {
    Series res;
    if (x <= -1) {
        std::cout << "Ошибка: ln(1+x) определен при x > -1\n";
        return res;
    }

    res.exactValue = log(1 + x);

    res.values.resize(maxZnach);
    res.sums.resize(maxZnach);
    res.errors.resize(maxZnach);

    res.values[0] = x;
    res.sums[0] = res.values[0];
    res.errors[0] = abs(res.sums[0] - res.exactValue);

    // X {n+1} = -X_n * (x * n / (n+1))
    for (int i = 1; i < maxZnach; i++) {
        res.values[i] = -res.values[i - 1] * (x * i / (i + 1));
    }
    return res;
}

Series calculateSumForward(const Series& inputSeries, int maxZnach) {
    Series res = inputSeries;

    for (int i = 1; i < maxZnach; i++) {
        res.sums[i] = res.sums[i - 1] + res.values[i];
        res.errors[i] = abs(res.sums[i] - res.exactValue);
    }

    return res;
}


Series calculateSumBackward(const Series& inputSeries, int maxZnach) {
    Series res = inputSeries;

    res.sums[maxZnach - 1] = res.values[maxZnach - 1];
    res.errors[maxZnach - 1] = abs(res.sums[maxZnach - 1] - res.exactValue);

    for (int i = maxZnach - 2; i >= 0; i--) {
        res.sums[i] = res.sums[i + 1] + res.values[i];
        res.errors[i] = abs(res.sums[i] - res.exactValue);
    }
    std::reverse(res.sums.begin(), res.sums.end());
    std::reverse(res.errors.begin(), res.errors.end());
    return res;
}


void printResults(const Series& series, int maxTerms) {
    std::cout << std::fixed << std::setprecision(10);
    std::cout << "\n РЕЗУЛЬТАТЫ \n";
    std::cout << "Точное значение функции: " << series.exactValue << "\n\n";
    std::cout << "Последнее значение: " << series.sums[maxTerms - 1] << "\n";
    std::cout << "Погрешность функции: " << series.errors[maxTerms - 1] << "\n\n";

    std::cout << "Таблица:\n";
    std::cout << "Кол-во слагаемых | Значение         | Ошибка\n";
    std::cout << "-----------------|------------------|------------------\n";

    for (int i = 0; i < maxTerms; i++) {
        std::cout << std::setw(16) << (i + 1) << " | ";
        std::cout << std::setw(16) << series.sums[i] << " | ";
        std::cout << std::setw(16) << series.errors[i] << "\n";
    }
}