#include<stdio.h>
int main()
{
	char a[100];
	gets(a);
	int n,i;
	for(n=0;a[n]!='\0';n++);
	i=(n+1)/2-1;
	printf("The central character of %s is %c.",a,a[i]);
	return 0;
 } 