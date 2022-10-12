#include <stdio.h>
#include<string.h>
int main(void)
{
	char S[99];
	int T;
	int Tlen;
	scanf("%c", &S);
	Tlen= strlen(S);
	T = (Tlen + 1) / 2;
	printf("%c", T);
	return 0;

}