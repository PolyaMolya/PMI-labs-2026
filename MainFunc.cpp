float rSin(float prev, float x, int n)
{
	if (n == 0) return x ;
	return prev * (-x * x) / ((2 * n) * (2 * n + 1));
}
float rCos(float prev, float x, int n)
{
	if (n == 0) return 1.0f;
	return prev * ((-x * x) / ((2 * n) * (2 * n - 1)));
}
float rExp(float prev, float x, int n)
{
	if (n == 0) return 1.0f;
	return prev * (x / n);
}
float rLn(float prev, float x, int n)
{
	if (n == 0) return 0;
	if (n == 1) return x;
	return prev * -x * (n - 1) / n;
}