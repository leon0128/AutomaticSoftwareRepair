#include<stdio.h>
main()
{
	char c[10];
	scanf("%s",c);
	if(c[1]=='o')
		printf("5");
	else if(c[1]=='u')
		printf("4");
	else if(c[1]=='e')
		printf("3");
	else if(c[1]=='h')
		printf("2");
	else
		printf("1");
}