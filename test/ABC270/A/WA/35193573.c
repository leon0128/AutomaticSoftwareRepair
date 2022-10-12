#include<stdio.h>
int main(void)
{
	int a,b,q;
	scanf("%d %d",&a,&b);
	if(a==b) printf("%d\n",a);
	else if(a+b>7) printf("7\n");
	else printf("%d\n",a+b);
	return 0;
}