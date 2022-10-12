#include <stdio.h>

int main(void)
{
	int x, y, n;
	scanf("%d %d %d", &x, &y, &n);

	int sum = 0;
	if (3 * x < y)
	{
		sum += x * n;
	}
	else
	{
		sum += (n / 3) * y;
		sum += (n % 3) * x;
	}

	printf("%d\n", sum);

	return 0;
}