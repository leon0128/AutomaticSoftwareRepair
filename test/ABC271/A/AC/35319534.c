#include<stdio.h>
int main()
{
	int n;
	scanf("%d", &n);
	if (n / 16 < 10)
		printf("%d", n / 16);
	else
		printf("%c", 'A' + n / 16 - 10);
	if (n % 16 < 10)
		printf("%d\n", n % 16);
	else
		printf("%c\n", 'A' + n % 16 - 10);
	return 0;
}