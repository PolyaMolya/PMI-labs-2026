#include <iostream>
using namespace std;

template <typename T>
class Vector {
protected:
    T* arr;
    int size;
public:
    Vector() {
        arr = nullptr;
        size = 0;
    }
    Vector(int n) {
        size = n;
        arr = new T[size];
        for (int i = 0; i < size; i++) {
            arr[i] = T();
        }
    }
    Vector(const Vector& other) {
        size = other.size;
        arr = new T[size];
        for (int i = 0; i < size; i++) {
            arr[i] = other.arr[i];
        }
    }
    Vector& operator=(const Vector& other) {
        if (this != &other) {
            delete[] arr;
            size = other.size;
            arr = new T[size];
            for (int i = 0; i < size; i++) {
                arr[i] = other.arr[i];
            }
        }
        return *this;
    }
    ~Vector() {
        delete[] arr;
    }
    T& operator[](int index) {
        if (index < 0 || index >= size) {
            throw "Index error!";
        }
        return arr[index];
    }
    const T& operator[](int index) const {
        if (index < 0 || index >= size) {
            throw "Index error!";
        }
        return arr[index];
    }
    int getSize() const {
        return size;
    }
};

template<typename T>
class matrix : public Vector<Vector<T>> {
protected:
    int size;
public:
    matrix(int n) : Vector<Vector<T>>(n), size(n) {
        for (int i = 0; i < size; i++) {
            (*this)[i] = Vector<T>(n);
        }
    }

    matrix(const matrix& other) : Vector<Vector<T>>(other), size(other.size) {}

    matrix& operator=(const matrix& other) {
        if (this != &other) {
            Vector<Vector<T>>::operator=(other);
            size = other.size;
        }
        return *this;
    }

    void input() {
        cout << "Matrix Element " << "\n";
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                cin >> (*this)[i][j];
            }
        }
    }
    void print() {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                cout << (*this)[i][j] << " ";
            }
            cout << endl;
        }
    }
    int getSize() const {
        return size;
    }
};

template <typename T>
class SLAU : public matrix<T> {
protected:
    matrix<T> savedMatrix;

public:
    using matrix<T>::input;
    using matrix<T>::print;

    SLAU(int n) : matrix<T>(n), savedMatrix(n) {}

    SLAU& operator=(const matrix<T>& other) {
        matrix<T>::operator=(other);
        return *this;
    }

    void saveMatrix() {
        savedMatrix = *this;
    }

    void swapRows(int row1, int row2) {
        if (row1 == row2) return;
        for (int j = 0; j < this->size; j++) {
            T temp = (*this)[row1][j];
            (*this)[row1][j] = (*this)[row2][j];
            (*this)[row2][j] = temp;
        }
    }

    bool findAndSwap(int k, Vector<T>& b) {
        if ((*this)[k][k] != 0) {
            return true;
        }
        for (int i = k + 1; i < this->size; i++) {
            if ((*this)[i][k] != 0) {
                swapRows(k, i);
                T temp = b[k];
                b[k] = b[i];
                b[i] = temp;
                return true;
            }
        }
        return false;
    }

    Vector<T> Gauss(Vector<T> b) {
        matrix<T>::operator=(savedMatrix);

        int n = this->size;

        for (int k = 0; k < n - 1; k++) {
            if (!findAndSwap(k, b)) {
                cout << "\nError: the matrix is virozhdena\n";
                return Vector<T>();
            }
            for (int i = k + 1; i < n; i++) {
                T koef = (*this)[i][k] / (*this)[k][k];
                for (int j = k; j < n; j++) {
                    (*this)[i][j] -= koef * (*this)[k][j];
                }
                b[i] -= koef * b[k];
            }
        }

        Vector<T> x(n);
        for (int i = n - 1; i >= 0; i--) {
            T sum = 0;
            for (int j = i + 1; j < n; j++) {
                sum += (*this)[i][j] * x[j];
            }
            x[i] = (b[i] - sum) / (*this)[i][i];
        }
        return x;
    }

    void printMtr(const Vector<T>& b) const {
        for (int i = 0; i < this->size; i++) {
            for (int j = 0; j < this->size; j++) {
                cout << (*this)[i][j] << " ";
            }
            cout << "| " << b[i] << "\n";
        }
    }

    void printRezh(const Vector<T>& x) const {
        for (int i = 0; i < this->size; i++) {
            cout << "x" << i + 1 << " = " << x[i] << "\n";
        }
    }
};

int main() {
    int n;
    cout << "Enter size: ";
    cin >> n;
    SLAU<double> a(n);
    a.input();
    a.saveMatrix();
    int choice = 1;
    while (choice != 0) {
        cout << "\n1. New vector" << endl;
        cout << "0. Exit" << endl;
        cout << "Choice: ";
        cin >> choice;
        if (choice == 1) {
            Vector<double> b(n);
            cout << "\nEnter vector b:\n";
            for (int i = 0; i < n; i++) {
                cout << "b[" << i + 1 << "] = ";
                cin >> b[i];
            }
            cout << "\nExtended matrix:\n";
            a.printMtr(b);
            Vector<double> rezhenie = a.Gauss(b);
            if (rezhenie.getSize() > 0) {
                cout << "\nRezhenie:\n";
                a.printRezh(rezhenie);
            }
        }
    }
    return 0;
}