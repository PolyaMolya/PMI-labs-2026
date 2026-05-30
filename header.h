#pragma once
#include <iostream>
#include <math.h>
#include <stdexcept>
using namespace std;
template <typename T>
class Moevector {
private:
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
	friend ostream& operator<<(ostream& os, const Moevector& v) {
		os << "Razmer: " << v.size << '\n' << "Vector: ";
		for (int i = 0;i < v.size;i++)
			os << v.infa[i] << ' ';
		return os;
	}
	Moevector& operator=(const Moevector& other) {
		size = other.size;
		delete[] infa;
		infa = new T[size];
		for (int i = 0;i < size;i++)
			infa[i] = other.infa[i];
		return (*this);
	}
	Moevector& operator -=(const Moevector& lhs) {
		for (int i = 0;i < size;i++)
			infa[i] -= lhs.infa[i];
		return *this;
	}
	friend Moevector operator *(T mnozh, Moevector hh) {
		Moevector result(hh.size);
		for (int i = 0;i < hh.size;i++)
			result.infa[i] = hh.infa[i] * mnozh;
		return result;
	}
	T& operator[](size_t index) {
		if (index >= size)
			cout << "Error index" <<'\n';
		return infa[index];
	}
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
class Moematrix {
protected:
	size_t msize;
	Moevector<Moevector<T>> minfa;
public:
	Moematrix() {
		msize = 0;
	}
	Moematrix(size_t size) {
		this->msize = size;
		minfa = Moevector<Moevector<T>>(size);
		for (size_t i = 0; i < size; i++) {
			minfa[i] = Moevector<T>(size);
		}
	}
	Moematrix(size_t size, Moevector<Moevector<T>>& infa) {
		msize = size;
		minfa = infa;
	}
	Moevector<T>& operator[](size_t index) {
		return minfa[index];
	}
	friend ostream& operator<<(ostream& os, const Moematrix<T>& m) {
		for (size_t i = 0; i < m.msize; i++) {
			os << m.minfa[i] << '\n';
		}
		return os;
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
		Moevector<T> reshenie=Moevector<T>(size);
		for (size_t i = 0;i < size;i++) {
			size_t maxrow = i;
			for (size_t k = i + 1;k < size;k++) {
				if (abs((*this)[k][i]) > abs((*this)[maxrow][i]))
					maxrow = k;
			}
			if (maxrow != i) {
				(*this)[i].swap((*this)[maxrow]);
				bswap(b[i], b[maxrow]);
			}
			if (abs((*this)[i][i]) ==0) {
				throw runtime_error("Matritsa virozhdena");
			}
			for (size_t j = i + 1;j < size;j++) {
				T mnozh = (*this)[j][i] / (*this)[i][i];
				(*this)[j] -= mnozh * (*this)[i];
				b[j] -= mnozh * b[i];
			}
		}
			for (int i = int(size) - 1;i >= 0;i--) {
				T sum = 0;
				for (size_t j = i + 1;j < size;j++)
					sum += (*this)[i][j] * reshenie[j];
				reshenie[i] = (b[i] - sum) / (*this)[i][i];
			}
			return reshenie;
		}
};