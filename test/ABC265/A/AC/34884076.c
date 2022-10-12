#include <stdio.h>

int	main(void)
{
	int	X;
	int	Y;
	int	N;

	scanf("%d %d %d", &X, &Y, &N);
	if (3 * X <= Y)
		printf("%d\n", X * N);
	else
		printf("%d\n", (Y * (N / 3)) + (X * (N % 3)));
	return (0);
}
