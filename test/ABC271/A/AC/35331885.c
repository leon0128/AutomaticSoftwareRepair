#include <stdio.h>

int main()
{
	int N;
	int a, b;

	scanf("%d", &N);

	a = N / 16;
	b = N % 16;

	if (a <= 9)
		printf("%d", a);
	else
		printf("%c", 'A' + a - 10);

	if (b <= 9)
		printf("%d\n", b);
	else
		printf("%c\n", 'A' + b - 10);

	return 0;
}
