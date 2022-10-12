#include<stdio.h>
#include<string.h>
int main()
{
	char s[99];
	scanf("%s",s);
	int i;
	i=strlen(s);
	int mid=i/2;
	printf("%c",s[mid]);
	return 0;
}