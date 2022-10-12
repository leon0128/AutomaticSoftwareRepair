#include <stdio.h>

int main()
{
	int N;
	scanf("%d", &N);
	if (N / 16 < 10) printf("%d", N / 16);
	else printf("%c", N / 16 + 'A' - 10);
	if (N % 16 < 10) printf("%d\n", N % 16);
	else printf("%c\n", N % 16 + 'A' - 10);
	fflush(stdout);
	return 0;
}