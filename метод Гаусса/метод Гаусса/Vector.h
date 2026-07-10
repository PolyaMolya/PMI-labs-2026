#pragma once

#include <vector>

//шаблонный класс вектор
template<typename T>
class Vector{
private:
    std::vector<T> data;
public:
    Vector(int n = 0) : data(n) {}
    int size() const{ return data.size();}

    T& operator[](int i) { return data[i];}
    const T& operator[](int i) const { return data[i];}
    void resize(int n) { data.resize(n);}
};
