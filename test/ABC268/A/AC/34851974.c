#include<stdio.h>
#define n 5
int main()
{
    int a[n],i;
    for(i=0;i<n;i++)
    scanf("%d",&a[i]);
    int j,t;
    for(i=0;i<n-1;i++)
    {
        for(j=0;j<n-1;j++)
        {
            if(a[j]>a[j+1])
            {
                t=a[j];
                a[j]=a[j+1];
                a[j+1]=t;
            }
        }
    }
    int count=0;
    for(i=0;i<n-1;i++)
    {
        if(a[i]!=a[i+1])
        {
            count++;
            continue;
        }
        else if(a[i]==a[i+1])
        {
            continue;
        }
    }
    printf("%d",count+1);
    return 0;
}