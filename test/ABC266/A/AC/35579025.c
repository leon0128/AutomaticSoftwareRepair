#include<stdio.h>
#include<string.h>

int main()
{
	char ch[255];
	gets(ch);
	int length = strlen(ch);
	printf("%c", ch[length / 2]);
	return 0;
}