#include<stdio.h>
int main()
{
	char s[102];
	scanf("%s", s);
	int n;
	for (n = 0; s[n] != '\0'; n++);
	printf("%c\n", s[n / 2]);
	return 0;
}