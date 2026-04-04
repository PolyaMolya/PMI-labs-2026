#include "headerr.h"
const int max = 100;
void initialization(struct ryad* cheto) {
	(*cheto).n = max;
	(*cheto).x = (float*)malloc((*cheto).n * sizeof(float));
	(*cheto).sum = (float*)malloc((*cheto).n * sizeof(float));
	(*cheto).err = (float*)malloc((*cheto).n * sizeof(float));
}
float nextsin(float prev, float x, int n) {
	return -x * x * prev / ((2 * n + 1) * (2 * n));
}
float nextcos(float prev, float x, int n) {
	return -x * x * prev / ((2 * n) * (2 * n - 1));
}
float nextexp(float prev, float x, int n) {
	return  x * prev / n;
}
float nextln(float prev, float x, int n) {
	return -x * prev * n / (n + 1);
}
void fill(struct ryad* infa, float(*func)(float prev, float x, int n), float x) {
	float first;
	initialization(infa);
	if (func == nextsin)
		first = x;
	if (func == nextcos)
		first = 1;
	if (func == nextexp)
		first = 1;
	if (func == nextln)
		first = x;
	(*infa).x[0] = first;
	float prev = first;
	for (int i = 1; i < (*infa).n; i++) {
		float next = func(prev, x, i);
		(*infa).x[i] = next;
		prev = next;
	}
}
float pryamosum(struct ryad* infa, int n) {
	float sum = 0;
	for (int i = 0; i < n; i++)
		sum += (*infa).x[i];
	return sum;
}
float obratnosum(struct ryad* infa, int n) {
	float sum = 0;
	for (int i = n - 1; i > -1; i--)
		sum += (*infa).x[i];
	return sum;
}
void Tylor(struct ryad* infa, float (*summetod)(struct ryad*, int), float pravda) {
	for (int i = 1; i < max + 1; i++) {
		(*infa).sum[i - 1] = summetod(infa, i);
		(*infa).err[i - 1] = fabs((*infa).sum[i - 1] - pravda);
	}
}
void vivodzn(struct ryad* infa, float(*mat)(float), float x) {
	Tylor(infa, pryamosum, mat(x));
	std::cout << "Pryamaya summa\n";
	for (int i = 0; i < max; i++)
		std::cout << "Kolvo chlenov " << 1 + i << " summa" << (*infa).sum[i] << " error" << (*infa).err[i] << '\n';
	Tylor(infa, obratnosum, mat(x));
	std::cout << "Obratnaya summa\n";
	for (int i = 0; i < max; i++)
		std::cout << "Kolvo chlenov " << i + 1 << " summa" << (*infa).sum[i] << " error" << (*infa).err[i] << '\n';
}
void menu() {
	std::cout << "Kakaya func?\n"<<"1.sin\n"<<"2.cos\n"<<"3.ln\n"<<"4.exp\n"<<"5.exit\n";
}