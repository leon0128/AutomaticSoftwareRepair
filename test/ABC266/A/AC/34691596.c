#include<stdio.h>
int main()
{
	char S[100];
	gets(S);
	int i=0;
	while(S[i]!=0)
	i++;
	printf("%c",S[i/2]);
}
