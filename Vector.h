#pragma once
#include <iostream> 

template <typename T>
class Vector {
protected:
	T* vec;
	unsigned int size;
public:
	Vector() { 
		size = 0;
		vec = nullptr;
	}
	Vector(int _size, T value = T()) {
		size = _size;
		vec = new T[size];
		for (int i = 0; i < size; i++) {
			vec[i] = value;
		}
	}
	Vector(const Vector& copy) { //Конструктор копирвоания
		size = copy.size;
		vec = new T[size];
		for (int i = 0; i < size; i++) {
			vec[i] = copy.vec[i];
		}
	}
	Vector& operator=(const Vector& rhs) { //Оператор присваивания
		if (this != &rhs) {
			delete[] vec;
			size = rhs.size;
			vec = new T[size];
			for (int i = 0; i < size; i++) {
				vec[i] = rhs.vec[i];
			}
		}
		return *this;
	}
	const T& operator[]( int index) const { // Перегрузка оператора [], чтобы использовать запис v[i], где v - Vector<T>
		return vec[index];
	}
	T& operator[](int index) {
		return vec[index];
	}
	void PrintVector() {
		for (int i = 0; i < size; i++) {
			std::cout << vec[i] << " ";
		}
	}
	void PrintVector2() {
		for (int i = 0; i < size; i++) {
			std::cout << vec[i] << "\n";
		}
	}
	void FillVector() {
		for (int i = 0; i < size; i++) {
			std::cin >> vec[i];
		}
	}
	int GetSize() const{
		return size;
	}
	~Vector() {
		delete[] vec;
	}
};
