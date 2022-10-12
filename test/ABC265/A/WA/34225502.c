#include <stdio.h>

int main() {
	int X, Y, N, A, B, C, a, b, D;
	scanf("%d %d %d", &X, &Y, &N);
	if (Y < 3 * X) {
		b = N / 3;
		a = N % 3;
		A = b * Y;
		B = a * X;
		C = A + B;
		printf("%d", C);
	}
	else {
		D = 10 * X;
		printf("%d", D);
	}
}