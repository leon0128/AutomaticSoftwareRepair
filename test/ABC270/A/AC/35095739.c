#include<stdio.h>
int main()
{
	int a,b;
	int p_4 = 0,p_2 = 0,p_1 = 0;
	scanf("%d %d",&a,&b);
	if(a == 1|| b == 1)
	{
		p_1 = 1;
	}
	if(a == 2||b == 2)
	{
		p_2 = 1;
	}
	if(a == 3||b == 3)
	{
		p_1 = p_2 = 1;
	}
	if(a == 4||b == 4)
	{
		p_4 = 1;
	}
	if(a == 5||b == 5)
	{
		p_1 = p_4 = 1;
	}
	if(a == 6|| b == 6)
	{
		p_2 = p_4 = 1;
	}
	if(a == 7|| b == 7)
	{
		p_1 = p_2 = p_4 = 1;
	}
	printf("%d",p_1 * 1+p_2 * 2+p_4 * 4);
}