#include "Header.h"

int main() {
    setlocale(LC_ALL, "Russian");

    double x;
    int maxTerms;
    int funcChoice;
    int sumChoice;
    Series result;

    // Выбор функции
    std::cout << " ВЫЧИСЛЕНИЕ ФУНКЦИЙ ЧЕРЕЗ РЯД ТЕЙЛОРА \n";
    std::cout << "Выберите функцию для вычисления:\n";
    std::cout << "1 - e^x\n";
    std::cout << "2 - sin(x)\n";
    std::cout << "3 - cos(x)\n";
    std::cout << "4 - ln(1+x)\n";
    std::cout << "Ваш выбор: ";
    std::cin >> funcChoice;

    // Ввод x
    std::cout << "\nВведите x: ";
    std::cin >> x;

  

    std::cout << "Введите максимальное количество членов ряда: ";
    std::cin >> maxTerms;

    // Выбор способа суммирования
    std::cout << "\nВыберите способ суммирования:\n";
    std::cout << "1 - Суммирование с начала (прямой порядок)\n";
    std::cout << "2 - Суммирование с конца (обратный порядок)\n";
    std::cout << "Ваш выбор: ";
    std::cin >> sumChoice;
    switch (funcChoice) {
    case 1:
        std::cout << "\nВыбрана функция: e^x";
        result = calculateEx(x, maxTerms);
        break;
    case 2:
        std::cout << "\nВыбрана функция: sin(x)";
        result = calculateSin(x, maxTerms);
        break;
    case 3:
        std::cout << "\nВыбрана функция: cos(x)";
        result = calculateCos(x, maxTerms);
        break;
    case 4:
        std::cout << "\nВыбрана функция: ln(1+x)";
        result = calculateLn(x, maxTerms);
        break;
    default:
        std::cout << "Неверный выбор функции!\n";
        return 1;
    }

    Series finalResult;
    if (sumChoice == 2) {
        finalResult = calculateSumBackward(result, maxTerms);
        std::cout << "\nИспользуется суммирование с конца";
    }
    else {
        finalResult = calculateSumForward(result, maxTerms);
        std::cout << "\nИспользуется суммирование с начала";
    }

    printResults(finalResult, maxTerms);

    return 0;
}