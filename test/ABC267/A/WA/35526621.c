#include<stdio.h> 
#include<stdlib.h> 
int main() 
{
	char *S;
	int b;
    S=(char *)malloc(sizeof(char));
    scanf("%s",S);
	if(S=="Monday") b=5;
	else if(S=="Tuesday") b=4;
	else if(S=="Wednesday") b=3;
	else if(S=="Thursday") b=2;
	else if(S=="Friday") b=1;
	printf("%d",b);
	return 0;
}
