// Laboratory_work_2.cpp : This file contains the 'main' function. Program execution begins and ends there.






#include <iostream>

template <typename T>
class My_vector {
protected:
	T* arr;
	unsigned size;
public:
	My_vector() {
		arr = nullptr;
		size = 0;
	}
	My_vector(unsigned _size) {
		size = _size;
		arr = new T[size];
	}
	My_vector(unsigned _size, T value=T()) {
		size = _size;
		arr = new T[size];
		for (unsigned int i = 0; i < size; i++) {
			arr[i] = value; 
		}
	}
	My_vector(const My_vector <T>& other) { //ok
		size = other.size;
		arr = new T[other.size];
		for (int i = 0; i < size; i++) {
			arr[i] = other.arr[i];
		}
	}	

	My_vector<T>& operator = (const My_vector<T>& other) {
		size = other.size;
		arr = new T[other.size];
		for (int i = 0; i < size; i++) {
			arr[i] = other.arr[i];
		}
		return (*this);
	}

	int GetSize() {
		return size;
	}
	void print() {  //ok
		for (int i = 0; i < size; i++) {
			std::cout << arr[i] <<' ';
		}
		std::cout << std::endl;
	}
	
	T& operator [] (int index) {
		if (index < size && index >= 0) {
			return arr[index];
		}
		else {
			//std::cout << "incorrect index";
			//return std::cerr << "incorrect index"; ошибка: cannot convert ... to T &
		}
	}
	
	unsigned get_size() {
		return size;
	}
	void set_size(unsigned _size) {
		size = _size;
	}
	void set_el(T el, int index) {  //ok
		arr[index] = el;
	}
	void swap(int a, int b) { //ok
		T tmp = arr[a];
		arr[a] = arr[b];
		arr[b] = tmp;
	}
	~My_vector() {
		delete[] arr;
		arr = nullptr;
		size = 0;
	}

	bool chek_first_zero(int ind) { //new
		bool f = 1;
		for (int i = 0; i < ind; i++) {
			if (arr[i] != 0) {
				f = 0;
			}
		}
		if (f == 1) {
			return true;
		}
		return false;
	}
	
};

template <typename T> 
class Matrix :public My_vector <My_vector<T>> {  //вектор векторов
protected:
public:
	Matrix(int _n) : My_vector<My_vector<T>>(_n, My_vector<T>(_n, 0)) { this->size = _n; };  

	Matrix(int _n, T a) : My_vector<My_vector<T>>(_n, My_vector<T>(_n, a)) { this->size = _n; };

	Matrix(const Matrix& other) : My_vector<My_vector<T>>(other) {
		this->size = other.size;
	}

	~Matrix() {}

	void print() {   //ok
		for (int i = 0; i < this->size; i++) {
			for (int j = 0; j < this->size; j++) {
				std::cout << this->arr[i][j] << ' ';
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
	My_vector<T>& operator [] (int i) {  
		if (i < this->size && i >= 0 ) {
			return this->arr[i];
		}
		else {
			//std::cout << "incorrect index";
			//return std::cerr << "incorrect index"; ошибка: cannot convert ... to T &
		}
	}
	
	void swap (int a, int b) { //row`s numbers
		My_vector<T> tmp = this->arr[a];
		this->arr[a] = this->arr[b];
		this->arr[b] = tmp;
	}
};
template <typename T>
class SLAU: public Matrix<T> {
private:
public:
	SLAU (int _n) : Matrix<T>(_n) {};
	SLAU(int _n, T a) : Matrix<T>(_n, a) {};
	~SLAU() {};

	My_vector<T> Gauss(My_vector<T> a) {
		if (this->size == 0)
			throw "error: Matrix`s size = 0";

		My_vector<T> answer = a; //копия правой части

		//к ступенчатосму виду
		for (int i = 0; i < this->size; i++) {
			if (this->arr[i][i] == 0) { //если на главной диагонали стоит 0, то меняем строки местами
				int j = i + 1;
				while (j < this->size && this->arr[j][i] == 0) {
					j++;
				}
				if (j == this->size) {
					throw "error: no solutions or infinite number of solutions";
				}
				this->swap(i, j);
				answer.swap(i, j);
			}
			for (int j = i + 1; j < this->size; j++) {
				T k = this->arr[j][i] / this->arr[i][i];  
				for (int h = 0; h < this->size; h++) {
					this->arr[j][h] -= k * this->arr[i][h];  //вычитаем из строки j строку i, умноженную на k
				}
				answer[j] -= k * answer[i];
			}
		}
		
		//матрица в ступенчатои виде

		answer[this->size - 1] = answer[this->size - 1] / this->arr[this->size - 1][this->size - 1];  //xn
		for (int j = this->size - 2; j >= 0; j--) {  //xi  пор строкам вверх
			for (int i = this->size - 1; i > j; i--) { //по столбцам влево
				answer[j] -= this->arr[j][i] * answer[i];
			}
			answer[j] = answer[j] / this->arr[j][j];
			
		}
		//
		

		return answer;
	}


	My_vector<T> Jordan_Gauss(My_vector<T> a) {
		if (this->size == 0)
			throw "error: Matrix`s size = 0";

		My_vector<T> answer = a; //копия правой части


		for (int i = 0; i < this->size; i++) {                //проход по столбцам, ведущий элемент
			//ведущий элеемент arr[i][i]
			//проверка на единственность решения
			for (int i = 0; i < this->size; i++) {
				bool f = 0;
				for (int j = 0; j < this->size; j++) {
					if (this->arr[i][j] != 0) {
						f = 1;
						break;
					}
				}
				if (f == 0) {
					//std::cout << "nulls row";
					throw "infinitely many solutions";
				}
			}
			if (this->arr[i][i] == 0) {   //если ведущий элемент ноль, то меняем строки местами
				for (int l = 0; l < this->size - 1; i++) {
					if (this->arr[l][i] != 0) {
						this->swap(i, l);
						answer.swap(i, l);
						i--; //чтобы после цикла i увеличился на единицу и мы не пропустили строку, которая стала i-й
						break;
					}
				}
			}
			for (int j = 0; j < this->size; j++) {

				if (i != j) {

					double k = this->arr[j][i] / this->arr[i][i];
					//вычитаем
					for (int h = 0; h < this->size; h++) {
						this->arr[j][h] -= k * this->arr[i][h];
					}
					answer[j] -= k * answer[i];
					//вычли 
				}

			}
		}
		
		//получили матрицу где все эл-ты кроме главной диагонали нули

		for (int i = 0; i < this->size; i++) {
			for (int j = 0; j < this->size; j++) {
				if (i == j) {
					answer[j] = answer[j] / this->arr[i][i];
					this->arr[i][i] = 1;
				}
			}
		}

		return answer;
	}

};



int main()
{

	std::cout << "enter size of matrix\n";
	int n; std::cin >> n;
	SLAU<double> m(n);
	std::cout << "enter matrix elements\n";
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			std::cin >> m[i][j];
		}
	}
	m.print();
	
	while (true) {
		std::cout << "enter the rigth part of sistem\n";
		My_vector<double> v(n, 1);
		for (int i = 0; i < n; i++) {
			std::cin >> v[i];
		}
		SLAU <double> copy_m = m;  
		std::cout << "choose the method: 1 - Gauss, 2 - Jordan-Gauss, 3 - exit";
		int choose; std::cin >> choose;
		if (choose == 1) {
			try {
				My_vector<double> ans = copy_m.Gauss(v);
				std::cout << "answer: ";
				ans.print();
			}
			catch (const char* error_mess) {
				std::cout << error_mess << "\n";
			}
		}
		else if (choose == 2) {
			try {
				My_vector<double> ans = copy_m.Jordan_Gauss(v);
				std::cout << "answer: ";
				ans.print();
			}
			catch (const char* error_mess) {
				std::cout << error_mess << "\n";
			}
		}
		else if (choose == 3)
			break;
		else
			std::cout << "error of choose\n";
		/*m.print();
		std::cout << std::endl;*/
	}
	
	
}



////вычитание из ответа всего кроме xi
//for (int j = this->size - 2; j > i; j--) {
//	for (int h = this->size - 1; h > j; h--) {
//		answer[j] -= answer[j + 1] * this->arr[j][h];
//	}
//
//}
//answer[i] = answer[i] / this->arr[i][i];
//
////std::cout << "i: "<< i << " j: "<< j<<" el: "<<this->arr[i][j] << std::endl;
//int k = this->arr[i][j] / this->arr[i][i];  //err: division by zero
//for (int h = 0; h < this->size; h++) {
//	this->arr[h][j] -= k * this->arr[h][i];  //вычитаем из строки j строку i, умноженную на k
//}
//answer[j] -= k * answer[i];
////a.print();
// 
// 
// 
//SLAU <double> m(3);
	//for (int i = 0; i < 3; i++) {
	//	for (int j = 0; j < 3; j++) {
	//		m[i][j] = i + j+2; 
	//	}
	//}
	////m[0][0] = 0;
	//m.print();
	//My_vector<double> v(3, 1);
	//v[1] = -2; v[2] = -4;
	////std::cout << "start gauss\n";

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
