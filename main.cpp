#include "header.h"
int main() {
	size_t size;
    cout << "Vvedite razmer matritsi" << '\n';
    cin >> size;
    Moevector<Moevector<double>> matrix(size);
    for (size_t i = 0; i < size; i++) {
        matrix[i] = Moevector<double>(size);
    }
    Moevector<double> b(size);
    cout << "Vvedite elementi matritsi A" << '\n';
    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < size; j++) {
            cin >> matrix[i][j];
        }
    }
     slau<double> system(matrix, size);
     int choice;
     while (true) {
         cout << "\n1. Vvod pravoy chasti\n2. Vihod\n";
         if (!(cin >> choice)) {
             cout << "Oshibka: vvedite chislo!\n";
             cin.clear();
             while (cin.get() != '\n');
             continue;
         }
         switch (choice) {
         case 1: {
             Moevector<double> b(size);
             cout << "Vvedite b: ";
             for (size_t i = 0; i < size; i++) cin >> b[i];
             try {
                 cout << "Reshenie: " << system.gauss(b) << "\n";
             }
             catch (const exception& e) {
                 cout << "Oshibka: " << e.what() << "\n";
             }
             break;
         }
         case 2:
             return 0;
         default:
             cout << "Nevernyy vybor\n";
             while (cin.get() != '\n');
         }
     }
}