#pragma once
#include <iostream>
#include <initializer_list>
template<typename T>
class Vector {
protected:
    T* a;
    int n;
public:
    // конструктор по умолчанию
    Vector() : a(nullptr), n(0) {}
    // конструктор с initializer_list
    Vector(std::initializer_list<T> t) {
         this->n = t.size();
        a = new T[n];
        int ii = 0;
        for (T i : t) {
            a[ii] = i;
            ii++;
        }
    }
    // конструктор с размером и значением
    Vector(int n, T k) : a(new T[n]), n(n) {
        for (int i = 0; i < n; ++i)
            a[i] = k;
    }
    //конструктор по размеру
    Vector(int n) : a(new T[n]), n(n) {}
    // конструктор копирования
    Vector(const Vector& other) : a(new T[other.n]), n(other.n) {
        for (int i = 0; i < n; ++i)
            a[i] = other.a[i];
    }

    // оператор присваивания
    Vector& operator=(const Vector& other) {
        if (this != &other) {
            delete[] a;
            n = other.n;
            a = new T[n];
            for (int i = 0; i < n; ++i)
                a[i] = other.a[i];
        }
        return *this;
    }

    // деструктор
    ~Vector() {
        delete[] a;
        a = nullptr;
    }

    // доступ по индексу
    T& operator[](int i) {
        if (i < 0 || i >= n) {
            throw "wrong index";
        }
        return a[i];
    }
    const T& operator[](int i) const { 
        if (i < 0 || i >= n) {
            throw "wrong index";
        }
        return a[i];
    }
    


    // умножение на скаляр
    void operator*=(T c) {
        for (int i = 0; i < n; ++i)
            a[i] *= c;
    }

    // вычитание вектора 
    void operator-=(const Vector& other) {
        for (int i = 0; i < n; ++i)
            a[i] -= other.a[i];
    }

    // умножение на скаляр
    Vector operator*(T c) const {
        Vector res (*this);
        res *= c;
        return res;
    }
    // свап векторов
    void swap(Vector& other) {
        T* tmp_a = a;
        a = other.a;
        other.a = tmp_a;
        int tmp_n = n;
        n = other.n;
        other.n = tmp_n;
    }
    // печать
    void print() const {
        for (int i = 0; i < n; ++i)
            std::cout << a[i] << "\n";
        std::cout << "\n";
    }

    int size() const { return n; }
};
template<typename T>
std::ostream& operator<<(std::ostream& os, const Vector<T>& v) {
    for (int i = 0; i < v.size(); ++i)
        os << v[i] << " ";
    return os;
}
template<typename T>
std::istream& operator>>(std::istream& is, Vector<T>& v) {
    for (int i = 0; i < v.size();++i)
        is >> v[i];
    return is;
}