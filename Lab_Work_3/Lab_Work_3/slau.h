#include <iostream>
#include <math.h>
#include <exception>

using namespace std;

template<typename T>
class Vector {
protected:
    T* data;
    int len;

public:
    Vector(int n = 0) : len(n) {
        data = new T[len];
        for (int i = 0; i < len; i++)
            data[i] = T();
    }

    ~Vector() {
        delete[] data;
    }

    Vector(const Vector& other) : len(other.len) {
        data = new T[len];
        for (int i = 0; i < len; i++)
            data[i] = other.data[i];
    }

    Vector& operator=(const Vector& other) {
        if (this != &other) {
            delete[] data;
            len = other.len;
            data = new T[len];
            for (int i = 0; i < len; i++)
                data[i] = other.data[i];
        }
        return *this;
    }

    int size() const {
        return len;
    }

    T& operator[](int index) {
        if (index >= len) {
            cout << "Oshibka: index " << index << " vne diapazona (razmer " << len << ")" << endl;
            return data[0];
        }
        return data[index];
    }

    const T& operator[](int i) const {
        if (i >= len) {
            cout << "Oshibka: index " << i << " vne diapazona (razmer " << len << ")" << endl;
            return data[0];
        }
        return data[i];
    }

    void swap(Vector& other) {
        T* tempData = data;
        data = other.data;
        other.data = tempData;

        int tempLen = len;
        len = other.len;
        other.len = tempLen;
    }
};

//  class matrix
template<typename T>
class Matrix: public Vector<Vector<T>>{
protected:
    int size_n;
public:
    Matrix(int n = 0) : Vector<Vector<T>>(n), size_n(n) {
        if (n < 0) {
            size_n = 0;
            Vector<Vector<T>>::Vector(0); 
        }
        for (int i = 0; i < size_n; i++) {
            Vector<T> row(size_n);
            Vector<Vector<T>>::operator[](i) = row;
        }
    }

    Matrix(const Matrix& other) : Vector<Vector<T>>(other), size_n(other.size_n) {}

    int razmer() const {
        return size_n;
    }

    Vector<T>& operator[](int index) {
        if (index >= size_n) {
            cout << "Oshibka: index " << index << " vne diapazona (razmer " << size_n << ")" << endl;
            return Vector<Vector<T>>::operator[](0);
        }
        return Vector<Vector<T>>::operator[](index);
    }

    void swapRows(int row1, int row2) {
        if (row1 >= 0 && row1 < size_n && row2 >= 0 && row2 < size_n && row1 != row2) {
            data[row1].swap(data[row2]);
        }
    }
};


template<typename T>
class SLAU : public Matrix<T> {
public:
    SLAU(int n) : Matrix<T>(n) {}

    Vector<T> gauss_jordan(Vector<T> pravo) {
        int n = this->razmer();


        if (n == 0) {
            cout << "Ошибка: матрица нулевого размера\n";
            return Vector<T>(0);
        }

        Matrix<T> a(n);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                a[i][j] = (*this)[i][j];

        Vector<T> b = pravo;

        for (int k = 0; k < n; k++) {

            int glavnaya = k;
            for (int i = k + 1; i < n; i++) {
                if (abs(a[i][k]) > abs(a[glavnaya][k]))
                    glavnaya = i;
            }


            if (abs(a[glavnaya][k]) < 1e-10) {
                cout << "Ошибка: матрица вырождена или система не имеет единственного решения\n";
                return Vector<T>(n);
            }


            if (glavnaya != k) {
                for (int j = 0; j < n; j++) {
                    T temp = a[k][j];
                    a[k][j] = a[glavnaya][j];
                    a[glavnaya][j] = temp;
                }
                T temp = b[k];
                b[k] = b[glavnaya];
                b[glavnaya] = temp;
            }


            T ved = a[k][k];
            if (abs(ved) < 1e-10) {
                cout << "Ошибка: нулевой ведущий элемент\n";
                return Vector<T>(n);
            }

            for (int j = k; j < n; j++)
                a[k][j] = a[k][j] / ved;
            b[k] = b[k] / ved;


            for (int i = 0; i < n; i++) {
                if (i != k) {
                    T mn = a[i][k];
                    for (int j = k; j < n; j++)
                        a[i][j] = a[i][j] - mn * a[k][j];
                    b[i] = b[i] - mn * b[k];
                }
            }
        }

        return b;
    }
};