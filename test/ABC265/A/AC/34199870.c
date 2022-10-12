#include<stdio.h>
int main()
{
	int x, y, n;
	scanf("%d %d %d", &x, &y, &n);
	if (3 * x > y)
		printf("%d\n", n / 3 * y + n % 3 * x);
	else
		printf("%d\n", n * x);
	return 0;
}