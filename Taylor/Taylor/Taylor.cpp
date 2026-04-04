#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct xn 
{
    int n;
    float* x;
    float* err;
    float* err_rev;
    float* sum;
    float* sum_rev;
};
void init(struct xn* data, int n) // Инициализация структуры
{
    data->n = n;
    data->x = (float*)malloc(n * sizeof(float));
    data->err = (float*)malloc(n * sizeof(float));
    data->err_rev = (float*)malloc(n * sizeof(float));
    data->sum = (float*)malloc(n * sizeof(float));
    data->sum_rev = (float*)malloc(n * sizeof(float));
}
void my_sin(struct xn* data, float x, int n)
{
    init(data, n);
    data->x[0] = x;  // Первый член
    data->sum[0] = data->x[0];

    float exact = sin(x); // Эталон
    float final_sum = data->sum[0];

    data->err[0] = fabs(data->sum[0] - exact); // Начальная ошибка

    for (int i = 0;i < n - 1;i++)
    {
        data->x[i + 1] = data->x[i] * (-x * x / ((2 * i + 2) * (2 * i + 3))); //Заполнения массива значений
        data->sum[i + 1] = data->sum[i] + data->x[i + 1];// Заполнение массива частичных сумм
        data->err[i + 1] = fabs(data->sum[i + 1] - exact); //Заполнение массива ошибки
    }


    data->sum_rev[n - 1] = data->x[n - 1];
    data->err_rev[n - 1] = fabs(data->sum_rev[n - 1] - exact);
    for (int i = n - 2; i >= 0; i--)
    {
        data->sum_rev[i] = data->sum_rev[i + 1] + data->x[i];
        data->err_rev[i] = fabs(data->sum_rev[i] - exact);
    }
}
void my_cos(struct xn* data, float x, int n)
{
        init(data, n);
        data->x[0] = 1.0;  // Первый член 
        data->sum[0] = data->x[0];

        float exact = cos(x); // Эталон
        float final_sum = data->sum[0];

        data->err[0] = fabs(data->sum[0] - exact); // Начальная ошибка

        for (int i = 0;i < n - 1;i++)
        {
            data->x[i + 1] = data->x[i] * (-x * x / ((2 * i + 1) * (2 * i + 2))); //Заполнения массива значений
            data->sum[i + 1] = data->sum[i] + data->x[i + 1];// Заполнение массива частичных сумм
            data->err[i + 1] = fabs(data->sum[i + 1] - exact); //Заполнение массива ошибки
        }


        data->sum_rev[n - 1] = data->x[n - 1];
        data->err_rev[n - 1] = fabs(data->sum_rev[n - 1] - exact);
        for (int i = n - 2; i >= 0; i--)
        {
            data->sum_rev[i] = data->sum_rev[i + 1] + data->x[i];
            data->err_rev[i] = fabs(data->sum_rev[i] - exact);
        }
}
void my_exp(struct xn* data, float x, int n)
{
    init(data, n);
    data->x[0] = 1;  // Первый член 
    data->sum[0] = data->x[0];

    float exact = exp(x); // Эталон
    float final_sum = data->sum[0];

    data->err[0] = fabs(data->sum[0] - exact); // Начальная ошибка

    for (int i = 0;i < n - 1;i++)
    {
        data->x[i + 1] = data->x[i] * x/(i+1); //Заполнения массива значений
        data->sum[i + 1] = data->sum[i] + data->x[i + 1];// Заполнение массива частичных сумм
        data->err[i + 1] = fabs(data->sum[i + 1] - exact); //Заполнение массива ошибки
    }


    data->sum_rev[n - 1] = data->x[n - 1];
    data->err_rev[n - 1] = fabs(data->sum_rev[n - 1] - exact);
    for (int i = n - 2; i >= 0; i--)
    {
        data->sum_rev[i] = data->sum_rev[i + 1] + data->x[i];
        data->err_rev[i] = fabs(data->sum_rev[i] - exact);
    }
}
void my_log(struct xn* data, float x, int n)
{
    init(data, n);
    data->x[0] = x;  // Первый член 
    data->sum[0] = data->x[0];

    float exact = log(x+1); // Эталон
    float final_sum = data->sum[0];

    data->err[0] = fabs(data->sum[0] - exact); // Начальная ошибка

    for (int i = 0;i < n - 1;i++)
    {
        data->x[i + 1] = -data->x[i] * x * (i + 1) / (i + 2); //Заполнения массива значений
        data->sum[i + 1] = data->sum[i] + data->x[i + 1];// Заполнение массива частичных сумм
        data->err[i + 1] = fabs(data->sum[i + 1] - exact); //Заполнение массива ошибки
    }


    data->sum_rev[n - 1] = data->x[n - 1];
    data->err_rev[n - 1] = fabs(data->sum_rev[n - 1] - exact);
    for (int i = n - 2; i >= 0; i--)
    {
        data->sum_rev[i] = data->sum_rev[i + 1] + data->x[i];
        data->err_rev[i] = fabs(data->sum_rev[i] - exact);
    }
}

void (*functions[4])(struct xn*, float, int) = { my_sin, my_cos, my_exp, my_log };
float (*etalon[4])(float) = { sin, cos, exp, log };

int main()
{
    struct xn data;

    printf("Choose your fucntion!\n 1: sin(x)\n 2: cos(x)\n 3: exp(x)\n 4: ln(x+1)\n");
    int choice;
    scanf_s("%d", &choice);

    printf("Set value for x (float)\n");
    float x;
    scanf_s("%f", &x);

    printf("Set number of members (int)\n");
    int n;
    scanf_s("%d", &n);
    while (n <= 0)
    {
        printf("The number must be positive, try again\n");
        scanf_s("%d", &n);
    }
    functions[choice - 1](&data, x, n);

    float exact;
    if (choice == 4)
        exact = etalon[3](x + 1);
    else
        exact = etalon[choice - 1](x);


    printf("Number\t Direct sum\t Reversed sum\t Expected\n");
    for (int i = 0; i < n; i++)
        printf("%d\t%.2e\t%.2e\t%.2e\n", i + 1, data.err[i], data.err_rev[i], exact);

    if (data.err[n - 1] > data.err_rev[0])
        printf("Reversed sum is more accurate\n");
    else
        printf("Direct sum is more accurate\n");
   

    free(data.x); free(data.err); free(data.err_rev); free(data.sum); free(data.sum_rev);
}
