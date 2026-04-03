#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <math.h>



struct Xn{
	int n;
	float* arr;
	float* sumF;
	float* errF;
	float* sumB;
	float* errB;
};

void Init(struct Xn* xn,int n1) {
	xn->n = n1;
	xn->arr = (float*)malloc(sizeof(float) * n1);
	xn->sumF = (float*)malloc(sizeof(float) * n1);
	xn->errF = (float*)malloc(sizeof(float) * n1);
	xn->sumB = (float*)malloc(sizeof(float) * n1);
	xn->errB = (float*)malloc(sizeof(float) * n1);
}

void Free(struct Xn* xn) {
	free(xn->arr);
	free(xn->sumF);
	free(xn->errF);
	free(xn->sumB);
	free(xn->errB);
}

void InitStateSinandLog(struct Xn* xn, float x) {
	xn->arr[0] = x;
}

void InitStateCosandExp(struct Xn* xn) {
	xn->arr[0] = 1.0f;
}

void Fill(struct Xn* xn, float x, float (*func)(float prev, float x, int n)) {
	int i;
	for (i = 1; i < xn->n; i++) {
		xn->arr[i] = func(xn->arr[i - 1], x, i);
	}
}

void Taylor(struct Xn* xn, void (*sum)(struct Xn*)) {
	sum(xn);
}

void SumForward(struct Xn* xn, float x, float (*f)(float)) {
	int i;
	float s = 0.0f;
	for (i = 0; i < xn->n; i++) {
		s = s + xn->arr[i];
		xn->sumF[i] = s;
		xn->errF[i] = xn->sumF[i] - f(x);
		if (xn->errF[i] < 0) {
			xn->errF[i] = -xn->errF[i];
		}
	}
}


void SumBack(struct Xn* xn, float x, float (*f)(float)) {
	int i;
	float s = 0.0f;
	for (i = 0; i <xn->n; i++) {
		s = s + xn->arr[xn->n - 1 -i];
		xn->sumB[i] = s;
		xn->errB[i] = xn->sumB[i] - f(x);
		if (xn->errB[i] < 0) {
			xn->errB[i] = -xn->errB[i];
		}
	}
}


float Exponenta(float prev, float x, int n) {
	return prev * x / n;
}

float Sinus(float prev, float x, int n) {
	return -prev * x * x / ((2 * n) * (2 * n + 1));
}

float Cosinus(float prev, float x, int n) {
	return -prev * x * x / ((2 * n) * (2 * n - 1));
}

float Logarifm(float prev, float x, int n) {
	return -prev * x * ((float)n / (n + 1));
}

void PrintArr(struct Xn* xn) {
	int i;
	printf("Члены ряда:\n");
	for (i = 0; i < xn->n; i++) {
		printf("%.1e ", xn->arr[i]);
	}
	printf("\n\n");
}

void PrintResult(struct Xn* xn) {
	int i;
	printf("Массив Сумм (с начала):\n");
	for (i = 0; i < xn->n; i++) {
		printf("%.6e ", xn->sumF[i]);
	}
	printf("\n\n");
	printf("Массив Ошибок (с начала):\n");
	for (i = 0; i < xn->n; i++) {
		printf("%.6e ", xn->errF[i]);
	}
	printf("\n\n");
	printf("Массив Сумм (с конца):\n");
	for (i = 0; i < xn->n; i++) {
		printf("%.6e ", xn->sumB[i]);
	}
	printf("\n\n");
	printf("Массив Ошибок (с конца):\n");
	for (i = 0; i < xn->n; i++) {
		printf("%.6e ", xn->errB[i]);
	}
	printf("\n\n");
}

