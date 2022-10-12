#include<stdio.h>

int main()
{
	int a[5]={0,0,0,0,0};
	scanf("%d %d %d %d %d",&a[0], &a[1], &a[2], &a[3], &a[4]);
	
	int i, j, x=5;
	for(i=0; i<4; i++)
	{
		for(j=i+1; j<5;j++)
		{
			if(a[i]==a[j])
			{
				a[j]=-j;
				x--;
			}
		}
	}
	
	printf("%d", x);
	
	return 0;
}