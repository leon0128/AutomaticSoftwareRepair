#include<stdio.h>
int main(void)
{
	int a,b,q;
	scanf("%d %d",&a,&b);
	if(a==b) printf("%d\n",a);
	else if(a>b&&a-b==1||b==1&&a==3) printf("%d\n",a);
	else if(b>a&&b-a==1||b==3&&a==1) printf("%d\n",b);
	else if(a+b>7) printf("7\n");
	else printf("%d\n",a+b);
	return 0;
}