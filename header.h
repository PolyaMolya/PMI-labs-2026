struct Xn {
    double X;
    double* Sum;
    double* Err;
    int N;
};

typedef double (*TaylorTermFunc)(double x, int n, double prev_term);

void calculate_taylor(double x, struct Xn* result, int max_n,
    TaylorTermFunc term_func,
    double (*exact_func)(double));

double sin(double x, int n, double prev_term);
double cos(double x, int n, double prev_term);
double exp(double x, int n, double prev_term);
double ln(double x, int n, double prev_term);

void free_results(struct Xn* result);
void print_errors(const struct Xn* sin_res, const struct Xn* cos_res, const struct Xn* exp_res, const struct Xn* ln_res, int max_n);
