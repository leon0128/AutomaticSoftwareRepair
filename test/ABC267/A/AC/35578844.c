#include<stdio.h>
#include<string.h>

int main()
{
	char a1[] = "Monday";
	char a2[] = "Tuesday";
	char a3[] = "Wednesday";
	char a4[] = "Thursday";
	char a5[] = "Friday";
	char Aim[10];
	gets(Aim);
	if(strcmp(Aim,a1)==0)
	printf("5");
	if(strcmp(Aim,a2)==0)
	printf("4");
	if(strcmp(Aim,a3)==0)
	printf("3");
	if(strcmp(Aim,a4)==0)
	printf("2");
	if(strcmp(Aim,a5)==0)
	printf("1");
	return 0;
}