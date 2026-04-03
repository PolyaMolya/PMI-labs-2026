#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <math.h>
#include "Taylor.h"
#include "stdlib.h"

using namespace std;  


void int_struct(struct Xn* xn, int n)
{
	xn->n = n;
	xn->x = (float*)malloc(n * sizeof(float));
	xn->err = (float*)malloc(n * sizeof(float));
	xn->sum = (float*)malloc(n * sizeof(float));
}

void free_struct(struct Xn* xn, int n)
{
	free(xn->x);
	free(xn->err);
	free(xn->sum);
}
enum TaylorMode{SIN, COS, LN, EXP};
void static universal(Xn* xn, float x, TaylorMode mode);
void compute_sin(Xn* xn, float x)
{
	universal(xn, x, SIN);
}
void compute_cos(Xn* xn, float x)
{
	universal(xn, x, COS);
}
void compute_ln(Xn* xn, float x)
{
	if (x <= -1.0f || x > 1.0f) {
		for (int i = 0; i < (xn->n); i++) {
			xn->x[i] = 0; xn->sum[i] = 0; xn->err[i] = 0;
		}
		return;
	}
	universal(xn, x, LN);
}
void compute_exp(Xn* xn, float x)
{
	universal(xn, x, EXP);
}
static float _sin(float x, int shag) {
	return (float)(-(x * x)/ ((2 * shag + 1) * (2 * shag)));
}
static float _cos(float x, int shag) {
	return (float)(-(x * x)/ ((2 * shag - 1) * (2 * shag)));
}
static float _ln(float x, int shag) {
	return (float)(-x * (shag) / (shag + 1));
}
static float _exp(float x, int shag) {
	return (float)(x / shag);
}

void static universal(Xn* xn, float x, TaylorMode mode) {
	float dobavka=0.0f;
	float gold_err=0.0f;
	switch (mode)
	{
	case SIN: dobavka = (float)x;
		gold_err = sin(x);
		break;
	case COS: dobavka = (float)1.0f;
		gold_err = cos(x);
		break;
	case LN: dobavka = (float)x;
		gold_err = log(1.0 + x);
		break;
	case EXP: dobavka = (float)1.0f;
		gold_err = exp(x);
		break;
	}
	float itog = dobavka;
	for (int i = 0; i < (xn->n); i++) {
		int reverse = (xn->n) - 1 - i;
		xn->x[reverse] = (float)dobavka;
		xn->sum[reverse] = (float)itog;
		xn->err[reverse] = (float)fabs(gold_err - itog);
		/*xn->x[i] = (float)dobavka;
		xn->sum[i] = (float)itog;
		xn->err[i] = (float)fabs(gold_err - itog);*/
		int shag = i + 1;
		float multiplier = 0;
		switch (mode)
		{
		case SIN: multiplier = _sin(x, shag);
			break;
		case COS: multiplier = _cos(x, shag);
			break;
		case LN: multiplier = _ln(x, shag);
			break;
		case EXP: multiplier = _exp(x, shag);
			break;
		}
		dobavka *= multiplier;
		itog += dobavka;
	}
}
void prepare_csv(const char* filename) {
	FILE* fp;
	fopen_s(&fp, filename, "w");
	if (fp != NULL) {
		fprintf(fp, "Результат;Погрешность\n");
		fclose(fp);
	}
}
void save_csv(Xn* xn, const char* func_name, const char* filename) {
	FILE* fp; 
	fopen_s(&fp, filename, "a");
	if (fp != NULL) {
		fprintf(fp, "--- %s ---\n", func_name);
		for (int i = 0; i < (xn->n); i++) {
			fprintf(fp, "%.8f;%.8f\n", (float)xn->sum[i], (float)xn->err[i]);
		}
		fprintf(fp, "\n");
		fclose(fp);
	}
}