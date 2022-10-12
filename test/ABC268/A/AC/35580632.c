#include<stdio.h>
int main()
{
	int i,arr[5],n,shu=5;
	for(i=0;i<5;i++)
	{
		scanf("%d",&arr[i]);
	}
	for(i=0;i<5;i++)
	{
		if(arr[i]>=0)
		{
			for(n=i+1;n<5;n++)
			{
				if(arr[i]==arr[n])
				{
					shu--;
					arr[n]=-1;
				}
			}
		}
	}
	printf("%d",shu);
		
	
}