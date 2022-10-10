#include<stdio.h>
int main()

{
	int i, N, A[100], sum = 0;
	scanf("%d", &N);

	for (i = 1; i <= N; i++)
	{
		scanf("%d", &A[i]);

	}
	for (i = 1; i <= N; i++)
	{
		sum = sum + A[i];
	}
	printf("%d\n", sum);

	return 0;
}