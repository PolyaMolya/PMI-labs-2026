#pragma once
struct Xn {
	int n;
	float* x;
	float* err;
	float* sum;
};
void int_struct(struct Xn* xn, int n);
void free_struct(struct Xn* xn, int n);
void compute_sin(struct Xn* xn, float x);
void compute_cos(struct Xn* xn, float x);
void compute_ln(struct Xn* xn, float x);
void compute_exp(struct Xn* xn, float x);
void prepare_csv(const char* filename);
void save_csv(Xn* xn, const char* func_name, const char* filename);