#include<stdio.h>
int main()
{
int a[10],i,k,count=0,t;
printf("please input the numbers:\n");
for(i=0;i<10;i++)
scanf("%d",&a[i]);
for(i=0;i<10;i++)
{t=0;
for(k=i-1;k>=0;k--)
if(a[i]==a[k])
t++;
if(t==0)
count++;
}
printf("the different numbers are :%d\n",count);
}