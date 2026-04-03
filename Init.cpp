#include <stdlib.h>
#include "Ryad.h"
#include <iostream>
#include <math.h>
#include "MainFunc.h"
#include "Filling.h"
void Init(struct Xn* r, int n)
{
	r->n = n;
	r->slagaemoe = (float*)malloc(sizeof(float) * n);
	r->starterr = (float*)malloc(sizeof(float) * n);
	r->enderr = (float*)malloc(sizeof(float) * n);
	r->startsum = (float*)malloc(sizeof(float) * n);
	r->endsum = (float*)malloc(sizeof(float) * n);
	if (r->slagaemoe && r->starterr && r->endsum && r->startsum && r->enderr)
	{
		for (int i = 0; i < n; i++)
		{
			r->slagaemoe[i] = 0.0f;
			r->starterr[i] = 0.0f;
			r->enderr[i] = 0.0f;
			r->startsum[i] = 0.0f;
			r->endsum[i] = 0.0f;
		}
	}
}
void FreeR(struct Xn* r)
{	
	if (r == NULL) return;
	r->n = 0;
	free(r->slagaemoe);
	free(r->starterr);
	free(r->enderr);
	free(r->startsum);
	free(r->endsum);
	r->startsum = NULL;
	r->endsum = NULL;
	r->starterr = NULL;
	r->enderr = NULL;
	r->slagaemoe = NULL;
}

