#include <stdio.h>
#include <string.h>

int main()
{
	int first=0,middle=0,last=0;
	char str[100]={0};
	gets(str);

	last=strlen(str);
	middle=(first+last)/2;

	putchar(str[middle]);
	printf("\n");

	return 0;
}