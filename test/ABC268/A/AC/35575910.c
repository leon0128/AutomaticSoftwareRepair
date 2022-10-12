#include <stdio.h>
int main()
{
	int arr[5];
	int i,j,a,c=0;
	for(i=0;i<5;i++)
	{
		scanf("%d",&arr[i]);
	}
	for(i=1;i<5;i++)
	{
		a=0;
		for(j=0;j<i;j++) if(arr[j]==arr[i])
		                  	{
				               a=1;
				               break;
			                }
	    if(a==0)
		{
		   a++;
		   c=c+a;	
		}   
		
		
	}
	printf("%d",c+1);
	return 0;
}