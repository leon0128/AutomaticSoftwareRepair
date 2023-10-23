#include <stdio.h>
int main(void)
{
	int year;
	int flag = 0;

	scanf("%d", &year);

	if (year % 4 == 0)
	{
		flag = 1;
	}
	if (year % 100 == 0)
	{
		flag = 0;
	}
	if (year % 400 == 0)
	{
		flag = 1;
	}

	if (flag)
	{
		printf("YES\n");
	}
	else
	{
		printf("NO\n");
	}

	return 0;
}