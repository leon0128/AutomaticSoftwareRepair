#include <stdio.h>
#include<string.h>
int main(void)
{
	char S[99];
	int T;
	scanf("%s", S);
	T=strlen(S);
	printf("%c", S[T / 2]);
	return 0;

}