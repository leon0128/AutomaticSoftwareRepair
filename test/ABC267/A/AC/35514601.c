#include <stdio.h>
#include <string.h>

int main()
{
	char a[10];
	scanf("%s",a);
	if(strcmp(a,"Monday")==0){printf("5");}
	
	else if(strcmp(a,"Tuesday")==0)printf("4");
		
	else if(strcmp(a,"Wednesday")==0)printf("3");
		
	else if(strcmp(a,"Thursday")==0)printf("2");
		
	else if(strcmp(a,"Friday")==0)printf("1");
			
	return 0;
}