#include<stdio.h>
int inornot(int t,int s[],int n)
{
	 int i;
	 for(i=0;i<n;i++)
	 {
	 	if(s[i]==t)
          return 0;
	 }
	 return 1;
}
int main()
{
	int i,t,s[5],n=0;
	for(i=0;i<5;i++)
	{
		scanf("%d",&t);
		if(inornot(t,s,n))
          s[n++]=t;
	}
	printf("%d\n",n);
	return 0;
}