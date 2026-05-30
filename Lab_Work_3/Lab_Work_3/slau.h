#include <iostream>
#include <math.h>

using namespace std;

// свой класс вектор
template<typename T>
class Vector {
private:
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

    T& operator[](int i) {
        return data[i];
    }

    const T& operator[](int i) const {
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

// класс матрица
template<typename T>
class Matrix {
protected:
    Vector<Vector<T>> data;
    int size_n;

public:
    Matrix(int n = 0) : size_n(n) {
        if (n < 0) n = 0;
        data = Vector<Vector<T>>(n);
        for (int i = 0; i < n; i++) {
            Vector<T> row(n);
            data[i] = row;
        }
    }

    int razmer() const {
        return size_n;
    }

    Vector<T>& operator[](int i) {
        return data[i];
    }

    const Vector<T>& operator[](int i) const {
        return data[i];
    }

    void swapRows(int row1, int row2) {
        if (row1 >= 0 && row1 < size_n && row2 >= 0 && row2 < size_n && row1 != row2) {
            data[row1].swap(data[row2]);
        }
    }
};

// класс слау
template<typename T>
class SLAU : public Matrix<T> {
public:
    SLAU(int n) : Matrix<T>(n) {}

    Vector<T> gauss_jordan(Vector<T> pravo) {
        int n = this->razmer();

        // защита от нулевого размера
        if (n == 0) {
            cout << "Ошибка: матрица нулевого размера\n";
            return Vector<T>(0);
        }

        // создаем копию матрицы
        Matrix<T> a(n);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                a[i][j] = (*this)[i][j];

        Vector<T> b = pravo;

        for (int k = 0; k < n; k++) {
            // поиск главного элемента
            int glavnaya = k;
            for (int i = k + 1; i < n; i++) {
                if (abs(a[i][k]) > abs(a[glavnaya][k]))
                    glavnaya = i;
            }

            // проверка на вырожденность
            if (abs(a[glavnaya][k]) < 1e-10) {
                cout << "Ошибка: матрица вырождена или система не имеет единственного решения\n";
                return Vector<T>(n);
            }

            // перестановка строк
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

            // деление строки на ведущий элемент
            T ved = a[k][k];
            if (abs(ved) < 1e-10) {
                cout << "Ошибка: нулевой ведущий элемент\n";
                return Vector<T>(n);
            }

            for (int j = k; j < n; j++)
                a[k][j] = a[k][j] / ved;
            b[k] = b[k] / ved;

            // обнуление остальных строк
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
