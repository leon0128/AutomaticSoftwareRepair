#include<stdio.h> 
#include<stdlib.h> 
int main() 
{
	char *S;
    S=(char *)malloc(sizeof(char));
    scanf("%s",S);
	if(S="Monday") printf("5");
	else if(S="Tuesday") printf("4");
	else if(S="Wednesday") printf("3");
	else if(S="Thursday") printf("2");
	else if(S="Friday") printf("1");
	return 0;
}
