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
    cout << "Vvedite vector b" << '\n';
    for (int i = 0;i < size;i++)
        cin >> b[i];
    try {
        slau<double> system(matrix, size);
        Moevector<double> reshenie = system.gauss(b);
        cout << "Reshenie sistemi: " << reshenie;
    }
    catch (exception e) { cout << "oshibka: " << e.what(); }
}