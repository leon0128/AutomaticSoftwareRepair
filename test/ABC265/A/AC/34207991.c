#include <stdio.h>

int main (void)
{
	int X, Y, N;
	scanf("%d %d %d",&X,&Y,&N);
	if (Y / 3  >= X)
	{
		printf("%d", N * X);
		return 0;
	}
	printf("%d", (N / 3) * Y + (N % 3) * X);
	
	return 0;
}