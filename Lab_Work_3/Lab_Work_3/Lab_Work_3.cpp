#include "slau.h"

int main() {
    setlocale(LC_ALL, "RU");

    int choice;

    do {
        int n;
        cout << "Vvedite razmer matricy: ";
        cin >> n;

        if (n <= 0) {
            cout << "Oshibka: razmer matricy dolzhen byt polozhitelnym\n";
            continue;
        }

        SLAU<double> slau(n);

        cout << "Vvedite matricu A:\n";
        for (int i = 0; i < n; i++) {
            cout << "Stroka " << i + 1 << " (cherez probel): ";
            for (int j = 0; j < n; j++) {
                cin >> slau[i][j];
            }
        }

        Vector<double> b(n);
        cout << "Vvedite vector pravoy chasti b (cherez probel): ";
        for (int i = 0; i < n; i++) {
            cin >> b[i];
        }

        Vector<double> x = slau.gauss_jordan(b);

        cout << "\nReshenie:\n";
        for (int i = 0; i < n; i++) {
            cout << "x" << i + 1 << " = " << x[i] << "\n";
        }

        cout << "\nHotite reshit s drugim vektorom? (1-da, 2-net): ";
        int reuse;
        cin >> reuse;

        while (reuse == 1) {
            Vector<double> b1(n);
            cout << "Vvedite drugoy vector b (cherez probel): ";
            for (int i = 0; i < n; i++) {
                cin >> b1[i];
            }

            Vector<double> x1 = slau.gauss_jordan(b1);

            cout << "\nReshenie:\n";
            for (int i = 0; i < n; i++) {
                cout << "x" << i + 1 << " = " << x1[i] << "\n";
            }

            cout << "\nHotite reshit s drugim vektorom? (1-da, 2-net): ";
            cin >> reuse;
        }

        cout << "\n1) Reshit novuyu matricu\n";
        cout << "2) Vyyty iz programmy\n";
        cin >> choice;

        while (choice != 1 && choice != 2) {
            cout << "Oshibka! Vvedite 1 ili 2: ";
            cin >> choice;
        }

        if (choice == 2) {
            cout << "\nProgramma zavershena\n";
        }

    } while (choice != 2);

    return 0;
}