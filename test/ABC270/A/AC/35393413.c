#include<stdio.h>
int  chai1(int n)
{
	int arr[4]={0,1,2,4};
	int x,y,z;
	for(x=0;x<4;x++)
	{
		for(y=0;y<4;y++)
		{
			for(z=0;z<4;z++)
			{
				if((arr[x]+arr[y]+arr[z]==n)&&(arr[x]<=arr[y])&&(arr[z]>=arr[y]))
				{
				
					return arr[x];
				}
			}
		}
		
	}

	
}
int  chai2(int n)
{
	int arr[4]={0,1,2,4};
	int x,y,z;
	for(x=0;x<4;x++)
	{
		for(y=0;y<4;y++)
		{
			for(z=0;z<4;z++)
			{
				if((arr[x]+arr[y]+arr[z]==n)&&(arr[x]<=arr[y])&&(arr[z]>=arr[y]))
				{
					
					return arr[y];
				}
			}
		}
		
	}
	
	
}
int  chai3(int n)
{
	int arr[4]={0,1,2,4};
	int x,y,z;
	for(x=0;x<4;x++)
	{
		for(y=0;y<4;y++)
		{
			for(z=0;z<4;z++)
			{
				if((arr[x]+arr[y]+arr[z]==n)&&(arr[x]<=arr[y])&&(arr[z]>=arr[y]))
				{
					
					return arr[z];
				}
			}
		}
		
	}
	
	
}
int he(int x,int y,int z,int a,int b,int c)
{
	int arr1[3]={x,y,z};
	int arr2[3]={a,b,c};
	int d=0;
	d=x+y+z+a+b+c;
	int n,m;
	for(n=0;n<3;n++)
	{
		for(m=0;m<3;m++)
		{
			if(arr1[n]==arr2[m])
			{
				d=d-arr1[n];
			}
		}
	}
	return d;
}
int main()
{
	int a,b;
	scanf("%d%d",&a,&b);
	int chengji=0;
	chengji=he((chai1(a)),(chai2(a)),(chai3(a)),(chai1(b)),(chai2(b)),(chai3(b)));
	printf("%d",chengji);
}