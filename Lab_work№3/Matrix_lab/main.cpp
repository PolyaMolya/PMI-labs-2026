#include <iostream>
#include <cmath>
using namespace std;

// Шаблонный класс Vector
template <typename T>
class Vector {
protected:
    T* arr;
    size_t size;
public:
    Vector(size_t size_ = 1, T value = 1) {
        size = size_;
        arr = new T[size];
        for (int i = 0; i < size; i++) arr[i] = value;
    }

    Vector(const Vector& other) {
        size = other.size;
        arr = new T[size];
        for (int i = 0; i < size; i++) arr[i] = other.arr[i];
    }

    size_t getS() const { return size; }

    Vector& operator=(const Vector& other) {
        if (this != &other) {
            delete[] arr;
            size = other.size;
            arr = new T[size];
            for (int i = 0; i < size; i++) arr[i] = other.arr[i];
        }
        return *this;
    }

    T& operator[](size_t i) {
        if (i >= size) cerr << "Out of range!\n";
        return arr[i];
    }

    const T& operator[](size_t i) const {
        if (i >= size) cerr << "Vector out of range!\n";
        return arr[i];
    }

    friend ostream& operator<<(ostream& os, const Vector<T>& V) {
        if (V.size > 0) {
            os << "[ ";
            for (int i = 0; i < V.size; i++) os << V.arr[i] << " ";
            os << "]";
        }
        return os;
    }

    friend istream& operator>>(istream& is, Vector<T>& V) {
        for (int i = 0; i < V.size; i++) is >> V.arr[i];
        return is;
    }

    ~Vector() {
        delete[] arr;
        arr = nullptr;
        size = 0;
    }
};

// Квадратная матрица как наследник Vector<Vector<T>>
template <typename T>
class Matrix : public Vector<Vector<T>> {
public:
    Matrix(size_t size_ = 1, T value = 1) : Vector<Vector<T>>(size_, Vector<T>(size_, value)) {}

    // Свап строк - для выбора ведущего элемента
    void swap(size_t row1, size_t row2) {
        if (row1 != row2) {
            Vector<T> temp = this->arr[row1];
            this->arr[row1] = this->arr[row2];
            this->arr[row2] = temp;
        }
    }

    Vector<T>& operator[](size_t i) {
        if (i >= this->size) cerr << "Out of range!\n";
        return this->arr[i];
    }

    const Vector<T>& operator[](size_t i) const {
        if (i >= this->size) cerr << "Out of range!\n";
        return this->arr[i];
    }

    friend ostream& operator<<(ostream& os, const Matrix<T>& M) {
        for (int i = 0; i < M.size; i++) os << M.arr[i] << "\n";
        return os;
    }

    friend istream& operator>>(istream& is, Matrix<T>& m) {
        for (int i = 0; i < m.size; i++)
            for (int j = 0; j < m.size; j++)
                is >> m[i][j];
        return is;
    }

    ~Matrix() {}
};

// СЛАУ - наследник Matrix с методом Гаусса
template <typename T>
class SLAE : public Matrix<T> {
public:
    SLAE(size_t size_ = 1, T value_ = 0) : Matrix<T>(size_, value_) {}

    // Метод Гаусса с выбором ведущего элемента
    Vector<T> gaussMethod(const Vector<T>& rightPart) {
        Matrix<T> A = *this;
        Vector<T> b = rightPart;
        size_t n = this->size;

        if (b.getS() != n) {
            cerr << "Error: Right part size doesn't match matrix size!\n";
            return Vector<T>(n, 0);
        }

        // Прямой ход с выбором ведущего элемента
        for (int k = 0; k < n; k++) {
            // Поиск максимального элемента в столбце
            int maxRow = k;
            T maxAbs = std::abs(A[k][k]);
            for (int i = k + 1; i < n; i++) {
                if (std::abs(A[i][k]) > maxAbs) {
                    maxAbs = std::abs(A[i][k]);
                    maxRow = i;
                }
            }

            if (maxAbs < 1e-10) {
                cerr << "Error: Matrix is singular!\n";
                return Vector<T>(n, 0);
            }

            // Свап строк при необходимости
            if (maxRow != k) {
                A.swap(k, maxRow);
                swap(b[k], b[maxRow]);
            }

            // Нормировка строки
            T pivot = A[k][k];
            for (int j = k; j < n; j++) A[k][j] /= pivot;
            b[k] /= pivot;

            // Исключение остальных строк
            for (int i = 0; i < n; i++) {
                if (i != k && std::abs(A[i][k]) > 1e-12) {
                    T factor = A[i][k];
                    for (int j = k; j < n; j++) A[i][j] -= factor * A[k][j];
                    b[i] -= factor * b[k];
                }
            }
        }
        return b;
    }
};

int main() {
    int n;

    cout << "Enter matrix size:\n";
    cin >> n;

    SLAE<double> a(n, 0);
    Vector<double> b(n, 0);

    cout << "Enter matrix:\n";
    cin >> a;

    cout << "Enter right path:\n";
    cin >> b;

    Vector<double> ans = a.gaussMethod(b);
    cout << "Solution:\n" << ans << "\n";
}