#include "rec_taylor_func.h"
float r_sin(float xn, int n,  float x) {
	return	x * x / ((2 * n + 2) * (2 * n + 3)) * xn * (-1);
}
float r_cos(float xn, int n, float x) {
	return	x * x / ((2 * n + 1) * (2 * n + 2)) * xn * (-1);
}
float r_exp(float xn, int n, float x) {
	return	x/(n+1)*xn;
}
float r_ln(float xn, int n, float x) {
	
	return -(x-1) * xn * (n + 1.0) / (n + 2.0);
}