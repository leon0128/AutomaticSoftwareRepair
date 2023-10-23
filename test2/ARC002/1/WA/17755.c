#include<stdio.h>
int main()
{
	int p,q,s,Y;
	1000 <= Y <= 2999;
	 p = 4;
	 q = 100;
	 s = 400;
	scanf("%d",&Y);
	if(Y / p == 0)
	{
		printf("YES\n");
	}else if(Y / q == 0)
	{
		printf("YES\n");
	}else if(Y / s ==0)
	{
		printf("YES\n");
	}else{
		printf("NO\n");
	}
	return 0;
}