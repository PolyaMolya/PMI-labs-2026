#include <stdio.h>
#include <math.h>
#include "header.h"

int main() {
    struct Xn sin_res, cos_res, exp_res, ln_res;
    int max_n;
    double x;

    printf("Enter max N: ");
    scanf_s("%d", &max_n);

    printf("Enter X value: ");
    scanf_s("%lf", &x);

    calculate_taylor(x, &sin_res, max_n, sin, sin);
    calculate_taylor(x, &cos_res, max_n, cos, cos);
    calculate_taylor(x, &exp_res, max_n, exp, exp);

    if (x > 0) {
        calculate_taylor(x, &ln_res, max_n, ln, log);
    }
    else {
        ln_res.X = x;
        ln_res.N = max_n;
        ln_res.Sum = NULL;
        ln_res.Err = NULL;
    }

    print_errors(&sin_res, &cos_res, &exp_res, &ln_res, max_n);

    free_results(&sin_res);
    free_results(&cos_res);
    free_results(&exp_res);
    free_results(&ln_res);
}