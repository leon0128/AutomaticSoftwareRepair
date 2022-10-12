#include <stdio.h>
int main(void)
{
	int X, Y, N,apple1,apple2,money1,money2,total;
	scanf("%d %d %d", &X, &Y, &N);
	apple1 = X / 1;
	apple2 = Y / 3;
	if (apple2 <=apple1) {
			apple2 = N / 3;
			apple1 = N % 3;
		}
	money1 = X * apple1;
	money2 = Y * apple2;
	printf("%d", money1+money2);
	return 0;
}