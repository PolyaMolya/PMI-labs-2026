
#include<math.h>
#include <iostream>
#include "rec_taylor_func.h"
typedef float (*math_func)(float x);
typedef float (*rec_func)(float xn, int n, float x);
enum class direction
{
    forward, backward, kahan, random
};
const int d = 4;
std::string dirs[d] = {"forward", "backward", "kahan", "random"};
direction dirs_[d] = { direction::forward, direction::backward, direction::kahan, direction::random };
enum class first_member {
    x, one, x1
};
struct Series
{
    const char* name;
    direction dir;//направление сложения
    math_func orig;//оригинальная функция для сравнения ошибки
    float true_value;//правильное значение
    first_member x0;
    
    rec_func next;//рекурентная функция ряда
    int n;//размер
    float x;//для какого икса считаем
    float* member;//члены ряда
    float* prev_sum;//префиксная или постфиксная сумма ряда
    float* err;//ошибка на этом шаге
    float res;//результат вычислений
    float r_err;//итоговая ошибка
    Series(const char* name, math_func orig, rec_func next, first_member x0) {
        this->name = name;
        this->orig = orig;
        this->next = next;
        this->x0 = x0;
        member = nullptr;
        prev_sum = nullptr;
        err = nullptr;
    }
};
int map(float a, float b, int na, int nb, float x) { 
    return (x - a) * (nb - na) / (b - a) + na;
}
void print_graph(Series a, int height) {
    float mx = 0;
    for (int i = 0; i < a.n; i++) {
        mx = std::max(mx, a.err[i]);
    }
    char** field;
    field = (char**)malloc(height * sizeof(char*));
    for (int i = 0; i < height; i++) {
        field[i] = (char*)malloc(a.n * sizeof(char));
        for (int j = 0; j < a.n; j++) {
            field[i][j] = ' ';
        }
    }
    for (int i = 0; i < a.n; i++) {
        int y = map(0, mx, 0, height - 1, a.err[i]);
        if (y < 0) y = 0;
        if (y >= height) y = height - 1;
        field[y][i] = '.';

    }
    for (int i = 0; i < height; i++) {
        std::cout << "|";
        for(int j = 0; j < a.n; j++)
        {
            std::cout << field[height - 1 -i][j];
        }
        std::cout << "\n";
        
    }
    std::cout<<"\\";
    for (int i = 0; i < a.n; i++) {
        std::cout << "_";
    }
    std::cout << "\n";
    for (int i = 0; i < height; i++) {
        
        free(field[i]);
    }
    free(field);
}
void fill(Series& s) {//должно быть заполнено всё кроме массивов и ...
    s.true_value = s.orig(s.x);
    free(s.member);
    free(s.prev_sum);
    free(s.err);
    s.member = (float*)malloc(sizeof(float) * s.n);
    s.prev_sum = (float*)malloc(sizeof(float) * s.n);
    s.err = (float*)malloc(sizeof(float) * s.n);
    s.member[0] = (s.x0 == first_member::x) ? s.x : 1;
    if (s.x0 == first_member::x1) {//особенности логарифма
        s.member[0] = s.x - 1;
    }
    for (int i = 1; i < s.n; i++) {
        s.member[i] = s.next(s.member[i - 1], i-1, s.x);
        //cout << s.member[i-1] << " ";
    }
    if (s.dir == direction::forward) {
        s.prev_sum[0] = s.member[0];
        s.err[0] = abs(s.prev_sum[0] - s.true_value);
        for (int i = 1; i < s.n; i++) {
            s.prev_sum[i] = s.prev_sum[i - 1] + s.member[i];
            s.err[i] = abs(s.prev_sum[i] - s.true_value);
            //cout << s.prev_sum[i] << " ";
        }
    }
    else if (s.dir == direction::backward) {
        s.prev_sum[0] = s.member[s.n - 1];
        s.err[0] = abs(s.prev_sum[0] - s.true_value);
        for (int i = 1; i < s.n; i++) {
            
            s.prev_sum[i] = s.prev_sum[i - 1] + s.member[s.n - i - 1];
            s.err[i] = abs(s.prev_sum[i] - s.true_value); 
            //cout << s.prev_sum[i] << " ";
        }
    }
    else if (s.dir == direction::kahan) {
        float sum = 0.0f;
        float c = 0.0f; 

        for (int i = 0; i < s.n; i++) {
            float y = s.member[i] - c;   
            float t = sum + y;
            c = (t - sum) - y;         
            sum = t;

            s.prev_sum[i] = sum;
            s.err[i] = abs(sum - s.true_value);
        }

        s.res = sum;
        s.r_err = s.err[s.n - 1];
    }//можно сделать способом кого-то там, если останется время
    else if (s.dir == direction::random) {
        int* order = (int*)malloc(s.n * sizeof(int));
        for (int i = 0; i < s.n; i++) order[i] = i;
        for (int i = s.n - 1; i > 0; i--) {
            int j = rand() % (i + 1);
            int tmp = order[i];
            order[i] = order[j];
            order[j] = tmp;
        }
        
        s.prev_sum[0] = s.member[order[0]];
        s.err[0] = abs(s.prev_sum[0] - s.true_value);
        for (int i = 1; i < s.n; i++) {
            s.prev_sum[i] = s.prev_sum[i - 1] + s.member[order[i]];
            s.err[i] = abs(s.prev_sum[i] - s.true_value);
        }

        s.res = s.prev_sum[s.n - 1];
        s.r_err = s.err[s.n - 1];

        free(order);
    }
    s.res = s.prev_sum[s.n - 1];
    s.r_err = s.err[s.n - 1];
}
void print_table(Series* s, int n_of_s, float* x, int n_of_x, int n_of_members, int height) {
    for (int i = 0; i < n_of_s; i++) {
        s[i].n = n_of_members; 
        s[i].x = x[0];
        std::cout << s[i].name << "(" << x[0] << ") = " << s[i].orig(x[0])<<"\n";

        for (int j = 0; j < d; j++) {
            std::cout <<"calculating " << dirs[j] << ":\n";
            s[i].dir = dirs_[j];
            fill(s[i]);
            print_graph(s[i], height);
            std::cout << s[i].name << "(" << x[0] << ") = " << s[i].res << ", error = " << s[i].r_err <<"\n";
        }
    }
    std::cout << "experiment with period:\n";
    std::cout << s[0].res << " " << s[0].r_err <<"\n";
    s[0].x += 2 * 3.14159265359;
    std::cout << " " << s[0].res <<" "<< s[0].r_err<<"\n";
    
}

int main()
{
    const int n_of_series = 4;
    Series a[n_of_series] = {
        Series("sin", sin, r_sin, first_member::x),
        Series("cos", cos, r_cos, first_member::one),
        Series("exp", exp, r_exp, first_member::one),
        Series("ln", log, r_ln, first_member::x1)
    };
    const int n_of_x = 5;//планировалось выводить для разных x, но в таком случае пришлось бы выводить слишком много всего
    float x[5] = {
        0.7, 1.2, 1.3, 1.4, 0.5
    };
    int n_of_members = 100 ;
    int height = 30;
    print_table(a, n_of_series, x, n_of_x, n_of_members, height);
}

