#include <stdio.h>

int main()
{
	int X, Y, N;
	scanf("%d %d %d", &X, &Y, &N);
	if (X * 3 <= Y) printf("%d\n", X * N);
	else printf("%d\n", X * (N % 3) + Y * (N / 3));
	fflush(stdout);
	return 0;
}