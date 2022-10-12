#include <stdio.h>

int a[101]; //全局变量默认值为0

int main()
{
	int i,x;
	int cnt=0;
	for(i=0;i<=4;i++)
	{
		scanf("%d",&x);
		if(a[x]==0)
		{
			cnt++;
			a[x]=1;
		}
	}
	printf("%d",cnt);
	return 0;
}