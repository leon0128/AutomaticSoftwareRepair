#include<stdio.h>
int main()
{
	char a[1010];
	gets(a);
	int n;
	for(n=0;a[n]!='\0';n++);
	printf("%c\n",a[n/2]);
	return 0;
 } 