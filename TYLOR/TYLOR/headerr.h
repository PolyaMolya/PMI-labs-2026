#pragma once
#include <stdlib.h>
#include <math.h>
#include <iostream>
struct ryad
{
	int n;
	float* x;
	float* err;
	float* sum;
};
void initialization(struct ryad* cheto);
float nextsin(float prev, float x, int n);
float nextcos(float prev, float x, int n);
float nextln(float prev, float x, int n);
float nextexp(float prev, float x, int n);
void fill(struct ryad* infa, float(*func)(float prev, float x, int n), float x);
float pryamosum(struct ryad* infa, int n);
float obratnosum(struct ryad* infa, int n);
void Tylor(struct ryad* infa, float (*summetod)(struct ryad*, int), float pravda);
void vivodzn(struct ryad* infa, float(*mat)(float), float x);
void menu();