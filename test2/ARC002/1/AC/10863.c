#include<stdio.h>

int yearcal(int y);

int main()
{
	int year;
	
	scanf("%d",&year); //input year
	
	printf("%s\n",yearcal(year)?"YES":"NO");
	
	return 0;
}

int yearcal(int y)
{
	return (0 == (y % 400)) || ((0 != (y % 100)) && (0 == (y % 4)));
}