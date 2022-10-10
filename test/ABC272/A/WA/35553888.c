#include<stdio.h>
int main()

{
	int i, N, AN;
	scanf("%d", &N);

	for (i = 1; i <= N; i++)
	{
		scanf("%d", &AN);

	}
	for (i = 1; i <= N; i++)
	{
		AN = AN + N;
	}
	printf("%d\n", AN);

	return 0;
}