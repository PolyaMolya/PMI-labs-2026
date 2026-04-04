#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "header.h"

void calculate_taylor(double x, struct Xn* result, int max_n,
    TaylorTermFunc term_func,
    double (*exact_func)(double)) {

    result->X = x;
    result->N = max_n;

    result->Sum = (double*)malloc(max_n * sizeof(double));
    result->Err = (double*)malloc(max_n * sizeof(double));

    double sum = 0.0;
    double prev_term = 0.0;

    for (int n = 0; n < max_n; n++) {
        double term = term_func(x, n, prev_term);
        prev_term = term;
        sum += term;
        result->Sum[n] = sum;
        result->Err[n] = fabs(sum - exact_func(x));
    }
}

double sin(double x, int n, double prev_term) {
    if (n == 0) return x;
    return prev_term * (-x * x) / ((2 * n) * (2 * n + 1));
}

double cos(double x, int n, double prev_term) {
    if (n == 0) return 1.0;
    return prev_term * (-x * x) / ((2 * n - 1) * (2 * n));
}

double exp(double x, int n, double prev_term) {
    if (n == 0) return 1.0;
    return prev_term * (x / n);
}

double ln(double x, int n, double prev_term) {
    double arg = x - 1.0;
    if (n == 0) return arg;
    return prev_term * (-arg * n / (n + 1));
}

void free_results(struct Xn* result) {
    if (result->Sum != NULL) {
        free(result->Sum);
        result->Sum = NULL;
    }
    if (result->Err != NULL) {
        free(result->Err);
        result->Err = NULL;
    }
}

void print_errors(const struct Xn* sin_res,
    const struct Xn* cos_res,
    const struct Xn* exp_res,
    const struct Xn* ln_res,
    int max_n) {

    printf("\n");
    printf(" N             sin(x)                cos(x)                exp(x)                ln(x)\n");
    for (int n = 0; n < max_n; n++) {
        printf("%d              %lf              %lf              %lf",
            n + 1,
            sin_res->Err[n],
            cos_res->Err[n],
            exp_res->Err[n]);

        if (ln_res->X > 0 && ln_res->Err != NULL) {
            printf("              %lf\n", ln_res->Err[n]);
        }
        else {
            printf("              \n", "undefined");
        }
    }
}
