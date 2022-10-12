#include<stdio.h>

int main(void)
{
	
	int i,j,k,o=0;
	int sum[5];
	for(i=0;i<5;i++)
	{
		scanf("%d",&sum[i]);
	}
	for(i=0;i<5;i++)
	{
		for(k=0,j=i+1;j<5;j++)
		{
			
			if( sum[j]!= sum[i])k++;
			
		}
		if(k==(4-i))o++;
			
		 
	}
	
	printf("%d",o);
}