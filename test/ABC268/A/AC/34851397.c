#include<stdio.h>
int main()
{
	int i=0,j,k,t,a[5],z=1;
	while(i<5)
	{
		do
		{
			scanf("%d",&a[i]);
		}while(a[i]<0||a[i]>100);
		i++;
	}
	for(i=0;i<4;i++)
		for(j=0;j<4-i;j++)
			if(a[j]<a[j+1])
			{
				t=a[j];
				a[j]=a[j+1];
				a[j+1]=t;
			}
	for(i=0;i<4;i++)
		if(a[i]!=a[i+1])
			z++;
	printf("%d",z);
	return 0;
}