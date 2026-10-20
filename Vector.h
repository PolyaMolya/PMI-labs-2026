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
	Vector(unsigned int _size, T value = T()) {
		if (_size == 0) {
			size = 0;
			vec = nullptr;
		}
		else {
			size = _size;
			vec = new T[size];
			for (int i = 0; i < size; i++) {
				vec[i] = value;
			}
		}
	}
	Vector(const Vector& copy) { 
		size = copy.size;
		vec = new T[size];
		for (int i = 0; i < size; i++) {
			vec[i] = copy.vec[i];
		}
	}
	Vector& operator=(const Vector& rhs) {
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
	const T& operator[]( int index) const {
		if (index < 0 || index >= size) {
			std::cout << "Ошибка! Выход за границы вектора" << "\n";
			return vec[0];
		}
		return vec[index];
	}
	T& operator[](int index) {
		if (index < 0 || index >= size) {
			std::cout << "Ошибка! Выход за границы вектора" << "\n";
			return vec[0];
		}
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
