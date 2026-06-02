#pragma once
#include <iostream>
#include <math.h>
#include <stdexcept>
using namespace std;
template <typename T>
class Moevector {
protected:
	size_t size;
	T* infa;
public:
	Moevector() {
		size = 0;
		infa = nullptr;
	}
	Moevector(size_t size) {
		this->size = size;
		infa = new T[size]();
	}
	Moevector(size_t size, T* infa_) {
		this->size = size;
		infa = new T[size];
		for (int i = 0;i < size;i++)
			infa[i] = infa_[i];
	}
	Moevector(const Moevector& other) {
		size = other.size;
		if (other.infa != nullptr) {
			infa = new T[size];
			for (size_t i = 0; i < size; i++)
				infa[i] = other.infa[i];
		}
		else {
			infa = nullptr;
		}
	}
	~Moevector() { delete[] infa; };
	Moevector& operator=(const Moevector& other) {
		size = other.size;
		delete[] infa;
		infa = new T[size];
		for (int i = 0;i < size;i++)
			infa[i] = other.infa[i];
		return (*this);
	}
	Moevector& operator-=(const Moevector& lhs) {
		if (size != lhs.size) {
			throw runtime_error("-= razniy razmer vectora");
		}
		for (size_t i = 0; i < size; i++)
			infa[i] -= lhs.infa[i];
		return *this;
	}
	Moevector operator*(T mnozh) {
		Moevector result(size);
		for (size_t i = 0; i < size; i++)
			result.infa[i] = infa[i] * mnozh;
		return result;
	}
	T& operator[](size_t index) {
		if (index >= size)
			throw out_of_range("Index out of range in Moevector");
		return infa[index];
	}
	friend ostream& operator<< <>(ostream& os, const Moevector<T>& v);
	void swap(Moevector<T>& other) {
		size_t temp = this->size;
		this->size = other.size;
		other.size = temp;
		T* temp_infa = this->infa;
		this->infa = other.infa;
		other.infa = temp_infa;
	}
};
template <typename T>
ostream& operator<<(ostream& os, const Moevector<T>& v) {
	os << "Razmer: " << v.size << '\n' << "Vector: ";
	for (int i = 0;i < v.size;i++)
		os << v.infa[i] << ' ';
	return os;
}
template <typename T>
class Moematrix :public Moevector<Moevector<T>>{
protected:
	size_t msize;
public:
	Moematrix() : Moevector<Moevector<T>>() {
		msize = 0;
	}
	Moematrix(size_t size) : Moevector<Moevector<T>>(size) {
		msize = size;
		for (size_t i = 0; i < size; i++) {
			(*this)[i] = Moevector<T>(size);
		}
	}
	Moematrix(size_t size, Moevector<Moevector<T>>& infa)
		: Moevector<Moevector<T>>(infa) {
		msize = size;
	}
	Moevector<T>& operator[](size_t index) {
		if (index >= msize) {
			throw out_of_range("vihod za matritsu");
		}
		return Moevector<Moevector<T>>::operator[](index);
	}
};
template <typename T>
void bswap(T& a, T& b) {
	T temp = a;
	a = b;
	b = temp;
}
template <typename T>
class slau :public Moematrix<T> {
public: 
	slau(Moevector<Moevector<T>> infa_, size_t size_):Moematrix<T>(size_, infa_) {}
	Moevector<T> gauss(Moevector<T> b) {
		size_t size = this->msize;
		Moevector<Moevector<T>> A = *this;
		Moevector<T> reshenie=Moevector<T>(size);
		for (size_t i = 0;i < size;i++) {
			size_t maxrow = i;
			for (size_t k = i + 1;k < size;k++) {
				if (abs(A[k][i]) > abs(A[maxrow][i]))
					maxrow = k;
			}
			if (maxrow != i) {
				A[i].swap(A[maxrow]);
				bswap(b[i], b[maxrow]);
			}
			if (abs(A[i][i]) ==0) {
				throw runtime_error("Matritsa virozhdena");
			}
			for (size_t j = i + 1;j < size;j++) {
				T mnozh = A[j][i] / A[i][i];
				A[j] -= A[i] * mnozh;
				b[j] -= mnozh * b[i];
			}
		}
			for (int i = int(size) - 1;i >= 0;i--) {
				T sum = 0;
				for (size_t j = i + 1;j < size;j++)
					sum += A[i][j] * reshenie[j];
				reshenie[i] = (b[i] - sum) / A[i][i];
			}
			return reshenie;
		}
};