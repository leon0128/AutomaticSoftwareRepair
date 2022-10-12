#include<stdio.h>
int main()
{
	int a[5] ,b[5];
	int i ,n ,k=0 ,m ;
	for(i=0 ;i<5 ;i++)
	{
		scanf("%d",&a[i]);
		if(a[i]>0&&a[i]<100)
		b[i]=a[i];
    }
	for(i=0 ;i<5 ;i++)
	{
		for(n=0 ;n<5 ;n++)
		{
			if(a[i]==b[n])
			k=k+1;
			break;
		}
	}
	m=5-k;
    printf("%d",m);
    return 0;
}
