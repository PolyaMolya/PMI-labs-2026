#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>

float sin_term(float current, float x, int n);
float cos_term(float current, float x, int n);
float exp_term(float current, float x, int n);
float ln_term(float current, float x, int n);

float pramayasum(float (*term_func)(float, float, int), float x, float first_term, int n);
float obratnayasum(float (*term_func)(float, float, int), float x, float first_term, int n);

int main() {
    setlocale(LC_ALL, "Russian");
    int choice;
    printf("Выберите функцию:\n");
    printf("1 — sin(x)\n");
    printf("2 — cos(x)\n");
    printf("3 — exp(x)\n");
    printf("4 — ln(1+x)\n");
    printf("Ваш выбор: ");
    scanf_s("%d", &choice);

    float x, exact_value, first_term;
    float (*term_func)(float, float, int);
    const char* func_name;

    switch (choice) {
    case 1:
        x = 10.0f;
        term_func = sin_term;
        first_term = x;
        exact_value = sinf(x);
        func_name = "sin(x)";
        break;
    case 2:
        x = 10.0f;
        term_func = cos_term;
        first_term = 1.0f;
        exact_value = cosf(x);
        func_name = "cos(x)";
        break;
    case 3:
        x = 4.0f;
        term_func = exp_term;
        first_term = 1.0f;
        exact_value = expf(x);
        func_name = "exp(x)";
        break;
    case 4:
        x = 0.9f;
        term_func = ln_term;
        first_term = x;
        exact_value = logf(1.0f + x);
        func_name = "ln(1+x)";
        break;
    default:
        printf("Неверный выбор!\n");
        return 1;
    }

    int n_max = 30;
    printf("\nФункция: %s\n", func_name);

    for (int n = 1; n <= n_max; n++) {
        float pramaya = pramayasum(term_func, x, first_term, n);
        float obratnaya = obratnayasum(term_func, x, first_term, n);

        float pramaya_error = fabsf(pramaya - exact_value);
        float obratnaya_error = fabsf(obratnaya - exact_value);

        printf("n=%d прямая погрешность=%e обратная погрешность=%e\n", n, pramaya_error, obratnaya_error);
    }
    return 0;
}

float sin_term(float current, float x, int n) {
    return current * (-x * x) / ((2 * n + 2) * (2 * n + 3));
}

float cos_term(float current, float x, int n) {
    return current * (-x * x) / ((2 * n + 1) * (2 * n + 2));
}

float exp_term(float current, float x, int n) {
    return current * x / (n + 1);
}

float ln_term(float current, float x, int n) {
    return current * (-x) * (n + 1) / (n + 2);
}

float pramayasum(float (*term_func)(float, float, int), float x, float first_term, int n) {
    float sum = first_term;
    float current = first_term;
    for (int i = 1; i < n; i++) {
        current = term_func(current, x, i - 1);
        sum += current;
    }
    return sum;
}

float obratnayasum(float (*term_func)(float, float, int), float x, float first_term, int n) {
    float* terms = (float*)malloc(n * sizeof(float));
    if (!terms) {
        printf("Ошибка выделения памяти!\n");
        exit(1);
    }
    terms[0] = first_term;
    float current = first_term;
    for (int i = 1; i < n; i++) {
        current = term_func(current, x, i - 1);
        terms[i] = current;
    }
    float sum = 0.0f;
    for (int i = n - 1; i >= 0; i--) {
        sum += terms[i];
    }
    free(terms);
    return sum;
}