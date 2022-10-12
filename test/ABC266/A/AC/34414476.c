#include<stdio.h>
#include<string.h>
int main(void)
{
	int n;
	char s[99];
	scanf("%s",s);
	n=strlen(s);
	n=(n-1)/2;
	printf("%c\n",s[n]);
	return 0;
}