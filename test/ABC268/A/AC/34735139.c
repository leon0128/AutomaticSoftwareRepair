#include <stdio.h>
#include<math.h> 
int main()
{
	int i,j,a[10],count=0,f;
	for(i=0;i<5;i++)
	{
		if(i==0)
		{
			scanf("%d",&a[0]);
			count++;
		}
		else
		{
			scanf("%d",&f);
			for(j=0;j<count;j++)
			{
				if(f==a[j])
				break;
			}
			if(j==count)
			{
				a[count]=f;
				count++;
			}
		}
	 } 
	 printf("%d",count);
 } 