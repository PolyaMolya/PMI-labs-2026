// Matrix_Lab3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;
/*Класс вектор*/
template <typename T>
class My_vector {
private:
    T* data;
    size_t size;
public:
    My_vector() {
        data = nullptr;
        size = 0;
    }
    My_vector(size_t size, T value = T()) {
        this->size = size;
        data = new T[size];
        for (int i = 0; i < size; i++) {
            data[i] = value;
        }
    }
    My_vector(const My_vector& other) {
        size = other.size;
        data = new T[size];
        for (int i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
    }
    My_vector operator=(const My_vector& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            data = new T[size];
            for (int i = 0; i < size; i++) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }
    My_vector operator*(T scalar) {
        My_vector result(size, T());
        for (int i = 0; i < size; i++) {
            result[i] = data[i] * scalar;
        }
        return result;
    }
    My_vector operator-(const My_vector& other) {
        My_vector result(size);
        for (int i = 0; i < size; i++) {
            result[i] = data[i] - other.data[i];
        }
        return result;
    }
    T& operator[](size_t index) {
        return data[index];
    }
    const T& operator[](size_t index) const {
        return data[index];
    }
    ~My_vector() {
        delete[] data;
    }
};

/*Класс Матриц*/
template<typename T>
class matrix:public My_vector<My_vector<T>> {
protected: 
    size_t n;
public:
    matrix(size_t n) : n(n), My_vector<My_vector<T>>(n, My_vector<T>(n, T())) {};
    void swapRows(int row1, int row2) {
        My_vector<T> temp = (*this)[row1];
        (*this)[row1] = (*this)[row2];
        (*this)[row2] = temp;
    }
    void input() {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                while (!(cin >> (*this)[i][j])) {
                    cout << "Incorrect input matrix! Enter numbers: ";
                    cin.clear();
                    cin.ignore(1000, '\n');
                }
            }
        }
    }
};
/*Класс СЛАУ*/
template<typename T>
class SLAY : public matrix<T> {
public:
    bool singular = false;
    SLAY(size_t n) : matrix<T>(n) {}
    My_vector<T> gauss(My_vector<T> b) {
        singular = false;
        size_t n = this->n;
        for (int i = 0; i < n; i++) {
            int maxRow = i;
            for (int k = i + 1; k < n; k++) {
                if (abs((*this)[k][i]) > abs((*this)[maxRow][i]))
                    maxRow = k;
            }
            this->swapRows(i, maxRow);
            T temp = b[i];
            b[i] = b[maxRow];
            b[maxRow] = temp;
            if (abs((*this)[i][i]) < 1e-10) {
                T bi = b[i];
                if (abs(bi) < 1e-10) cout << "\nInfinitely many solutions.";
                else cout << "\nThere are no solutions.";
                singular = true;
                return My_vector<T>(n, T());
            }
            for (int j = i + 1; j < n; j++) {
                T scalar = (*this)[j][i] / (*this)[i][i];
                (*this)[j] = (*this)[j] - (*this)[i] * scalar;
                b[j] = b[j] - b[i] * scalar;
                
            }
        }   
        My_vector<T> x(n, T());
        for (int i = n - 1; i >= 0; i--) {
            x[i] = b[i];
            for (int j = i + 1; j < n; j++) {
                x[i] = x[i] - (*this)[i][j] * x[j];
            }
            x[i] = x[i] / (*this)[i][i];
        }
        return x;
    }
    void printSlay(My_vector<T> b) {
        size_t n = this->n;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout  << setw(8) << (*this)[i][j];
            }
            cout << " |" << setw(8) << b[i] << endl;
        }
    }
};
int main(){   
    int size;
    cout << "Select the matrix size: ";
    while (!(cin >> size) || size <= 0) {
        cout << "Error. Please enter a positive number: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }

    SLAY<double> origin(size);
    cout << "\nEnter the matrix " << size << "x" << size << ":" << endl;
    origin.input();

    char again = 'y';
    while (again == 'y') {
        SLAY<double> copy = origin;
        My_vector<double> b(size);
        cout << "\nEnter the right part :" << endl;
        for (int i = 0; i < size; i++) {
            cout << "b[" << i + 1 << "] = ";
            while (!(cin >> b[i])) {
                cout << "Incorrect input right part! Enter numbers: ";
                cin.clear();
                cin.ignore(1000, '\n');
            }
        }
        cout << "\nStart matrix: " << endl;
        copy.printSlay(b);
        My_vector<double> x = copy.gauss(b);
        if (copy.singular) {
            cout << "\nSystem does haven't a unique solution." << endl;
        }
        else {
            cout << "\nAnswer:" << endl;    
            for (int i = 0; i < size; i++) {
                if (x[i] == 0.0) {
                    x[i] = 0.0;
                    cout << "x" << i << " = 0" << endl;
                }
                else {
                    cout << "x" << i + 1 << " = " << x[i] << endl;
                }

            }
        }
        cout << "\nDo you want to change the right part and solve with the dame matrix again?\nIf you wan - enter 'y': ";
        cin >> again;
    }
    
    return 0;
}
