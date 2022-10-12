#include<stdio.h>
int a[200] ;
int main()
{
	int i ;
	int b ;
	for(i = 0 ; i < 5 ; i++)
	{
		scanf("%d",&b);
		a[b]++;
	}
	int count = 0 ;
	for(i = 0 ; i < 200 ; i++)
	{
		if(a[i] > 0)
		{
			count++;	
		}	
	} 
	printf("%d",count);
	return 0 ;
}