#include<stdio.h>

int main()
{
	int i;
	scanf("%d",&i);
	if(i%4==0)
	{
		if(i%100==0)
		{
			if(i%400==0)
			{
				printf("YES\n");
				return 0;
			}
			printf("NO\n");
			return 0;
		}
		printf("YES\n");
		return 0;
	}
	printf("NO\n");
}
