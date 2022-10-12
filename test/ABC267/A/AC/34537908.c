#include <stdio.h>

int main()
{
	char day[10];

	scanf("%s", day);

	if(day[0]=='M')
	{
		printf("%d\n", 5);
	}
	else if(day[0]=='W')
	{
		printf("%d\n", 3);
	}
	else if(day[0]=='F')
	{
		printf("%d\n", 1);
	}
	else
	{
		if(day[1]=='u')
		{
			printf("%d\n", 4);
		}
		else
		{
			printf("%d\n", 2);
		}
	}
	return(0);
}