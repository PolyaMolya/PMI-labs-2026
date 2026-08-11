#include <iostream>
#include <stdio.h>
#include <stdexcept>
using namespace std;



template <typename T>
class MyVector
{
protected:
	T* mas = nullptr;
	int size = 0;
public:
	MyVector() : mas(nullptr), size(0) {}

	MyVector(int n): size(n)
	{
		mas = new T[n];
	}
	MyVector(const MyVector& other) : size(other.size) //Конструктор копирования
	{
		mas = new T[size];
		for (int i = 0; i < size;i++)
		{
			mas[i] = other.mas[i];
		}
	}
	MyVector& operator =(const MyVector& other) // Перегрузка присваивания
	{
		if (this == &other)
			return *this;
		delete[] mas;

		size = other.size;
		mas = new T[size];
		for (int i = 0; i < size;i++)
		{
			mas[i] = other.mas[i];
		}
		return *this;
	}
	~MyVector() // Деструктор
	{
		delete[] mas;
		mas = nullptr;
		size = 0;
	}

	T& operator[](int i) // Для обращения по индексу
	{ 
		return mas[i];

	}

	int Getsize()
	{
		return size;
	}

	void input()
	{
		for (int i = 0; i < size;i++)
		{
			cin >> mas[i];
		}
	}

	void print() 
	{
		for (int i = 0;i < size;i++)
			cout << mas[i] << " ";
		cout << endl;
	}

};

template <typename T>
class Matrix : public MyVector<MyVector<T>>
{
protected:
	int size_m;
public:
	Matrix (int size) : MyVector < MyVector<T>>(size), size_m(size)
	{
		for (int i = 0; i < size_m;i++)
		{
			(*this)[i] = MyVector<T>(size_m);
		}
	}
	void swap (int r1, int r2)
	{
		MyVector<T> temp = (*this)[r1];
		(*this)[r1] = (*this)[r2];
		(*this)[r2] = temp;
	}
	void input_m()
	{
		for (int i = 0; i < size_m; i++)
		{
			for (int j = 0; j < size_m; j++)
			{
				cin >> (*this)[i][j];
			}
		}
	}

	void print_m()
	{
		for (int i = 0; i < size_m; i++)
		{
			(*this)[i].print();
			cout << endl;
		}
	}
};

template <typename T>
class SLAU : public Matrix<T>
{
private:
	bool isZero(T val)
	{
		return abs(val) < 1e-10;
	}

public:
	SLAU(int size) : Matrix<T>(size) {}

	void printWhole(MyVector<T>& b)
	{
		for (int i = 0; i < this->size_m; i++)
		{
			for (int j = 0; j < this->size_m; j++)
			{
				cout << (*this)[i][j] << " ";
			}
			cout << "| " << b[i] << endl;
		}
	}

	MyVector<T> Gauss_Jordan(MyVector<T> b)
	{
		int n = this->size_m;

		// Копии
		Matrix<T> a = *this;
		MyVector<T> right = b;

		for (int k = 0; k < n; k++)
		{
			// 1. Ищем главный элемент в столбце k
			int glav = k; // Строка где самый большой элемент
			T maxZnach = abs(a[k][k]);

			for (int i = k + 1; i < n; i++)
			{
				if (abs(a[i][k]) > maxZnach)
				{
					maxZnach = abs(a[i][k]);
					glav = i;
				}
			}
			// 2. Проверка на нулевой столбец
			if (isZero(maxZnach))
			{
				bool flag = false;
				for (int i = k; i < n; i++)
				{
					if (!isZero(right[i]))
					{
						flag = true;
						break;
					}
				}

				if (flag)
					throw runtime_error("No solutions");
				else
					throw runtime_error("Infinite number of solutions");
			}

			// 3. Меняем строки местами, если нужно
			if (glav != k)
			{
				a.swap(k, glav);          
				swap(right[k], right[glav]); 
			}

			// 4. Делим строку на главный элемент
			T del = a[k][k];
			for (int j = k; j < n; j++)
			{
				a[k][j] = a[k][j] / del;
			}
			right[k] = right[k] / del;

			// 5. Вычитаем из остальных строк ведущую, умноженную на текущий элемент 
			for (int i = 0; i < n; i++)
			{
				if (i != k)
				{
					T mult = a[i][k];
					for (int j = k; j < n; j++)
					{
						a[i][j] = a[i][j] - mult * a[k][j];
					}
					right[i] = right[i] - mult * right[k];
				}
			}
		}

		return right;
	}
};
int main()
{
		int n;
		cout << "Input size of square matrix: ";
		cin >> n;

		SLAU<double> system(n);

		cout << "Input matrix A (" << n << "x" << n << "):" << endl;
		system.input_m();

		char repeat;
		do
		{
			MyVector<double> b(n);
			cout << "Input right part b:" << endl;
			b.input();

			cout << "\n The system looks like:" << endl;
			system.printWhole(b);


			try
			{
				MyVector<double> x = system.Gauss_Jordan(b);
				cout << "Solutions are: " << endl;
				x.print();
				cout << endl;
			}
			catch (const runtime_error& e)
			{
				cout << "Error: " << e.what() << endl;
			}
			cout << "Want to input new right part? (Y/N) ";
			cin >> repeat;
		} while (repeat == 'Y');
}