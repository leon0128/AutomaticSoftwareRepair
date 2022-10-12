#include <stdio.h>
#include <string.h>
int main()
{
	char day[10]={0};
	int left=0;
	gets(day);
	if (strcmp(day,"Monday")==0) 
	{
		left=5;
		printf("%d\n",left);
	}
	else if(strcmp(day,"Tuesday")==0)
	{
		left=4;
		printf("%d\n",left);
	} 
	else if(strcmp(day,"Wednesday")==0)
	{
		left=3;
		printf("%d\n",left);
	} 
	else if(strcmp(day,"Thursday")==0)
	{
		left=2;
		printf("%d\n",left);
	} 
	else if(strcmp(day,"Friday")==0)
	{
		left=1;
		printf("%d\n",left);
	} 
	return 0;
}