#include<stdio.h>
#include<string.h>
int main()
{
	char a[99];
	scanf("%s", &a);
	int length = strlen(a);
	if (length == 1)
	{
		printf("%c\n", a[0]);
	}
	else
	{
		length /= 2;
		printf("%c\n", a[length]);
	}

	return 0;
}