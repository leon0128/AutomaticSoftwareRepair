#include<stdio.h>
char a[16]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
int main()
{
	int as;
	scanf("%d",&as);
	printf("%c%c\n",a[as/16],a[as%16]);
	return 0;
}