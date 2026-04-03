#include <iostream>
#include <locale>
#include "Init.h"
#include "Ryad.h"
#include "Filling.h"
#include "MainFunc.h"
#include "PrintRyad.h"
int main()
{
	setlocale(LC_ALL, "Russian");
	//setlocale(LC_NUMERIC, "C");
	struct Xn Taylor;
	int n;
	float x;
	int choice;
	printf("Введите количество членов ряда\n");
	scanf_s("%d", &n);
	Init(&Taylor, n);
	printf("Выберите точку\n");
	scanf_s("%f", &x);
	printf("Выберите функцию\n");
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
	printf("1.sin(x)\n2.cos(x)\n3.exp\n4.ln(x+1)\n");
	scanf_s(" %d", &choice);
	if (choice <= 4 && choice >= 1)
	{
		choices(choice, &Taylor, x);
		PrintR(&Taylor);
	}
	FreeR(&Taylor);
}

