// лабораторная2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программ
#include <iostream>
#include "stdio.h"
#include "stdlib.h"
#include "math.h"

struct Teylor {
	int n; //кол-во слагаемых
	float* x;//массив значений
	float* err;//массив погрешностей
	float* sum;//массив частичных сумм
};

void init(Teylor* xn, int n) {
	xn->n = n;
	xn->x = (float*)malloc(n * sizeof(float));
	xn->err = (float*)malloc(n * sizeof(float));
	xn->sum = (float*)malloc(n * sizeof(float));
}

void clean(Teylor* xn) {
	free(xn->x);
	free(xn->err);
	free(xn->sum);
}

void sum_left(Teylor* xn) {
	xn->sum[0] = xn->x[0];
	for (int i = 1; i < xn->n; i++) {
		xn->sum[i] = xn->sum[i - 1] + xn->x[i];
	}
}

void sum_right(Teylor* xn) {
	xn->sum[0] = xn->x[xn->n - 1];
	for (int i = 1; i < xn->n; i++) {
		xn->sum[i] = xn->sum[i - 1] + xn->x[xn->n - i - 1];
	}
}

void Teylor_sin(Teylor* xn, float x, void(*sum)(Teylor* xn)) {
	xn->x[0] = x;
	for (int i = 1; i < xn->n; i++) {
		xn->x[i] = (-1) * x * x * xn->x[i - 1] / ((2 * (i - 1) + 2) * (2 * (i - 1) + 3));
	}
	sum(xn);
}

void Teylor_cos(Teylor* xn, float x, void(*sum)(Teylor* xn)) {
	xn->x[0] = 1;
	for (int i = 1; i < xn->n; i++) {
		xn->x[i] = (-1) * (x * x * xn->x[i - 1]) / ((2 * (i - 1) + 1) * (2 * (i - 1) + 2));
	}
	sum(xn);
}

void Teylor_exp(Teylor* xn, float x, void(*sum)(Teylor* xn)) {
	xn->x[0] = 1;
	for (int i = 1; i < xn->n; i++) {
		xn->x[i] = (x * xn->x[i - 1]) / ((i - 1) + 1);
	}
	sum(xn);
}

void Teylor_ln(Teylor* xn, float x, void(*sum)(Teylor* xn)) {
	xn->x[0] = x;
	for (int i = 1; i < xn->n; i++) {
		xn->x[i] = ((-1) * x * (i)*xn->x[i - 1]) / (i + 1);
	}
	sum(xn);
}

void err_fill(Teylor* xn, float x, float(*func_math)(float)) {
	for (int i = 0; i < xn->n; i++) {
		xn->err[i] = abs((func_math(x)) - (xn->sum[i]));
	}
}

void print(Teylor xn) {
	printf("n\tf(x)\t       err\n\n");
	for (int i = 0; i < xn.n; i++) {
		printf("%d\t%.7f\t%.7f\n", i + 1, xn.sum[i], xn.err[i]);
	}
	printf("\n");
}

void fill_print(void(*func_Teylor)(Teylor* xn, float x, void(*sum)(Teylor* xn)), Teylor a, Teylor b, float x1, float x2, float(*func_math)(float x)) {
	func_Teylor(&a, x1, sum_left);
	func_Teylor(&b, x1, sum_right);

	err_fill(&a, x2, func_math);
	err_fill(&b, x2, func_math);

	print(a);
	print(b);
}

void start_menu() {
	printf("Select function:\n");
	printf("1 - sin(x)\n");
	printf("2 - cos(x)\n");
	printf("3 - exp(x)\n");
	printf("4 - ln(x)\n");
	printf("0 - exit\n\n");
}

void Point(int point) {
	printf("Enter n:");
	printf("\n");
	int n;
	scanf_s("%d", &n);
	printf("\n");

	Teylor a, b;

	init(&a, n);
	init(&b, n);

	float x = 0.7f;

	switch (point) {
	case 1:
		fill_print(Teylor_sin, a, b, x, x, sin);
		break;
	case 2:
		fill_print(Teylor_cos, a, b, x, x, cos);
		break;
	case 3:
		fill_print(Teylor_exp, a, b, x, x, exp);
		break;
	case 4:
		fill_print(Teylor_ln, a, b, x, x+1, log);
		break;
	default:
		printf("try again please\n\n");
		break;
	}
	clean(&a);
	clean(&b);
}

int main()
{
	while (true) {
		start_menu();

		int point;
		scanf_s("%d", &point);

		if (point == 0) {
			break;
		}
		else {
			Point(point);
			printf("\n");
		}
	}
}


// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
