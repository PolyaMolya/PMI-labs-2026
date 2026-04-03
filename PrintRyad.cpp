#include <iostream>
#include "Ryad.h"
#include <locale>
void PrintR(struct Xn* r)
{
	
	printf("Ryad\n");
	for (int i = 0; i < r->n; i++)
	{
		printf("%.4e  ", r->slagaemoe[i]);
	}
	printf("\n\n");
	printf("StartZnach\n");
	printf("%.10f\n\n", r->startsum[r->n-1]);
	printf("StartSumm\n");
	for (int i = 0; i < r->n; i++)
	{
		printf("%.4e  ", r->startsum[i]);
	}
	printf("\n\n");
	printf("StartErrors\n");
	for (int i = 0; i < r->n; i++)
	{
		printf("%.4e  ", r->starterr[i]);
	}
	printf("\n\n");
	printf("EndZnach\n");
	printf("%.10f\n\n", r->endsum[r->n - 1]);
	printf("EndSumm\n");
	for (int i = 0; i < r->n; i++)
	{
		printf("%.4e  ", r->endsum[i]);
	}
	printf("\n\n");
	printf("EndErrors\n");
	for (int i = 0; i < r->n; i++)
	{
		printf("%.4e  ", r->enderr[i]);
	}
	printf("\n");
}