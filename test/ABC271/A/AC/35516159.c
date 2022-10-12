#include <stdio.h>
#include <stdlib.h>

int main()
{
	char *c = "0123456789ABCDEF";
	int n;
	scanf("%d", &n);
	char answer[] = "00\0";
	int i = 1;
	while (n > 0)
	{
		answer[i] = c[n % 16];
		n /= 16;
		i--;
	}
	printf("%s\n", answer);
	return 0;
}