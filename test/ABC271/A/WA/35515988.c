#include <stdio.h>
#include <stdlib.h>

int main()
{
	char *c = "0123456789ABCDEF";
	int n;
	scanf("%d", &n);
	char answer[3];
	int i = 0;
	while (n > 0)
	{
		answer[i] = c[n % 16];
		n /= 16;
		i++;
	}
	if (i == 2)
	{
		char temp = answer[0];
		answer[0] = answer[1];
		answer[1] = temp;
	}
	answer[i] = '\0';
	printf("%s\n", answer);
	return 0;
}