#include <stdio.h>
int main(void)
{
	int N, M, T;
	int i, j;
	long A[100001], X[100001], Y[10001];
	scanf("%d %d %d\n", &N, &M, &T);
	for (i = 1; i < N - 1; i++) {
		scanf("%d", A);
		A[i] = A[i] + A[i + 1];
	}
	for (j = 0; j < M;j++) {
		scanf("%d %d\n", X,Y);
		Y[j] = Y[j] + Y[j + 1];
	}

	if (A - Y < T) {
		printf("yes");
	}
	else {
		printf("no");
	}
	return 0;
}

