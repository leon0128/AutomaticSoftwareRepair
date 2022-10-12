#include <stdio.h>

int main() {
	int X, Y, N, A, B, C, a, b;
	scanf("%d %d %d", &X, &Y, &N);
	b = N / 3;
	b = b * 3;
	a = N - b;
	b = b / 3;
	A = b * Y;
	B = a * X;
	C = A + B;
	printf("%d", C);
	return 0;
}