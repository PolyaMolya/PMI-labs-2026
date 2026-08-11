#include <math.h>
#include "MainFunc.h"
#include <iostream>
#include "Ryad.h"
void Fill(struct Xn* r, float(*function)(float prev, float x, int n), float x)
{
	r->slagaemoe[0] = function(0.0f, x, 0);
	for (int i = 1; i < r->n; i++)
	{
		r->slagaemoe[i] = function(r->slagaemoe[i-1], x, i);
	}
}
void Errors(struct Xn* r, float(*etalon)(float x), float x)
{
	float et = etalon(x);
	for (int i = 0; i < r->n; i++)
	{
		r->starterr[i] = fabs(et - r->startsum[i]);
	}
	for (int i = 0; i < r->n; i++)
	{
		r->enderr[i] = fabs(et - r->endsum[i]);
	}
}
void Sum(struct Xn* r)
{
	r->endsum[0] = r->slagaemoe[r->n - 1];
	r->startsum[0] = r->slagaemoe[0];
	for (int i = 1; i < r->n; i++)
	{
		r->startsum[i] = r->slagaemoe[i] + r->startsum[i - 1];
	}
	for (int i = 1; i < r->n; i++)
	{
		r->endsum[i] = r->slagaemoe[r->n -1 -i] + r->endsum[i - 1];
	}
}
void choices(int choice, struct Xn* r, float x)
{
	float(*function)(float prev, float x, int n) = NULL;
	float(*etalon)(float x) = NULL;
	switch (choice)
	{
	case 1: function = rSin; etalon = sinf; break;
	case 2: function = rCos; etalon = cosf; break;
	case 3: function = rExp; etalon = expf; break;
	case 4: function = rLn; etalon = log1pf; break;
	default: printf("Error"); return;
	}
	Fill(r, function, x);
	Sum(r);
	Errors(r, etalon, x);
}