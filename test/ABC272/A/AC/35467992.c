#include <stdio.h>

int main()
{
	int i, N, A, sum = 0;
	scanf("%d", &N);
	for (i = 1; i <= N; i++) {
		scanf("%d", &A);
		sum += A;
	}
	printf("%d\n", sum);
	fflush(stdout);
	return 0;
}