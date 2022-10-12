#define  _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
int main()
{
	int a = 0;
	scanf("%d", &a);
	while (getchar() != '\n');
	char arr[] = { "123456789abcdef" };
	char hex[16];
	int i = 0;
	while (a)
	{
		hex[i++] = arr[a % 16];
		a / 16;
	}
	return 0;
}