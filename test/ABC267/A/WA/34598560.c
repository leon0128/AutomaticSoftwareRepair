#include<stdio.h>

int main(void)
{
	char s[9];

	scanf("%s", &s);
	if (s == "Monday")
	{
		printf("5");
		return 0;
	}
	else if(s == "Tuesday")
	{
		printf("4");
		return 0;
	}
	else if (s == "Wednesday")
	{
		printf("3");
		return 0;
	}
	else if (s == "Thursday")
	{
		printf("2");
		return 0;
	}
	else
	{
		printf("1");
		return 0;
	}
}