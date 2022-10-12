#include<stdio.h>
int main()
{
	int x,y,n;
	scanf("%d%d%d",&x,&y,&n);
	if(x*3<=y)
	{
		printf("%d",x*n);
	}
	else
	{
		int count=n/3;
		int rem=n-(count*3);
		printf("%d",count*y+x*rem);
	}
	return 0;
}
