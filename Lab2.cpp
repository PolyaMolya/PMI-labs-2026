#include <iostream>
#include <cmath>
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
        return arr[index];
    }

    const T& operator[](int index) const {
        return arr[index];
    }

    int getSize() const {
        return size;
    }
};
template<typename T>
class matrix {
protected:
    Vector<Vector<T>> data;
    int size;
public:
    matrix(int n) : size(n), data(n) {
        for (int i = 0; i < size; i++) {
            data[i] = Vector<T>(n);
        }
    }
    matrix(const matrix& other) : size(other.size), data(other.size) {
        for (int i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
    }
    matrix& operator=(const matrix& other) {
        if (this != &other) {
            size = other.size;
            data = Vector<Vector<T>>(size);
            for (int i = 0; i < size; i++) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }
    void input() {
        cout << "Matrix Element: " << " \n";
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                cin >> data[i][j];
            }
        }
    }
    void print() {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                cout << data[i][j] << " ";
            }
            cout << " \n";
        }
    }
    Vector<T>& operator[](int index) {
        return data[index];
    }

    const Vector<T>& operator[](int index) const {
        return data[index];
    }

    int getSize() const {
        return size;
    }
};
template <typename T>
class SLAU : public matrix<T> {
public:
    using matrix<T>::input;
    using matrix<T>::print;
    void swapRows(matrix<T>& A, int row1, int row2) {
        if (row1 == row2) return;
        for (int j = 0; j < this->size; j++) {
            T temp = A[row1][j];
            A[row1][j] = A[row2][j];
            A[row2][j] = temp;
        }
    }
    bool findAndSwap(matrix<T>& A, int k, Vector<T>& b) {
        if (A[k][k] != 0) {
            return true;
        }
        for (int i = k + 1; i < this->size; i++) {
            if (A[i][k] != 0) {
                swapRows(A, k, i);
                T temp = b[k];
                b[k] = b[i];
                b[i] = temp;
                return true;
            }
        }
        return false;
    }
    SLAU(int n) : matrix<T>(n) {}
    Vector<T> Gauss(Vector<T> b) {
        matrix<T> A = *this;
        Vector<T> B = b;
        int n = this->size;
        for (int k = 0; k < n - 1; k++) {
            if (!findAndSwap(A, k, B)) {
                cout << "\nError: the matrix is virozdena\n";
                return Vector<T>();
            }
            for (int i = k + 1; i < n; i++) {
                T koef = A[i][k] / A[k][k];
                for (int j = k; j < n; j++) {
                    A[i][j] -= koef * A[k][j];
                }
                B[i] -= koef * B[k];
            }
        }
        if (A[n - 1][n - 1] == 0 || abs(A[n - 1][n - 1]) < 1e-10) {
            cout << "\nError: the matrix is virozdena\n";
            return Vector<T>();//навсякий случай
        }
        Vector<T> x(n);
        for (int i = n - 1; i >= 0; i--) {
            T sum = 0;
            for (int j = i + 1; j < n; j++) {
                sum += A[i][j] * x[j];
            }
            x[i] = (B[i] - sum) / A[i][i];
        }
        return x;
    }
    void printMtr(const Vector<T>& b) const {
        for (int i = 0; i < this->size; i++) {
            for (int j = 0; j < this->size; j++) {
                cout << this->data[i][j] << " ";
            }
            cout << b[i] << " \n";
        }
    }
    void printRezh(const Vector<T>& x) const {
        for (int i = 0; i < this->size; i++) {
            cout << "x" << i + 1 << " = " << x[i] << " \n";
        }
    }
};

int main() {
    int n;
    cout << "Enter size: ";
    cin >> n;
    SLAU<double> a(n);
    a.input();
    Vector<double> b(n);
    cout << "\nEnter vector b:\n";
    for (int i = 0; i < n; i++) {
        cout << "b[" << i + 1 << "] = ";
        cin >> b[i];
    }
    a.printMtr(b);
    Vector<double> rezhenie = a.Gauss(b);
    if (rezhenie.getSize() > 0) {
        a.printRezh(rezhenie);
    }
    return 0;
}