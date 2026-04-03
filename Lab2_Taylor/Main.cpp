#include <stdio.h>
#include "Taylor.h"
#include <iostream>
#include "math.h"
using namespace std;
int main() {
	struct Xn d;
	int n = 10;
	float x = 0.707f;
	
	const char* Myfile = "lab.results.csv";
	prepare_csv(Myfile);

	int_struct(&d, n);
	compute_exp(&d, x);
	save_csv(&d,"EXP(X)", Myfile);
	cout << "The results are stored in the \"lab.results\" file.";
	/*cout << "LN " << x << endl;
	for (int i = 0; i < n; i++) {
		printf("Shag %d: Sum = %.7f (Err: %.7g)\n", i, d.sum[i], d.err[i]);
	}*/

	
	free_struct(&d, n);
	return 0;
}