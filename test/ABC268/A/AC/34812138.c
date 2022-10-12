
#include <stdio.h>

int main() 
{
    int a[10],count=1,m;
    for(int i=1;i<=5;i++)
        scanf("%d",&a[i]);
    for(int i=1;i<=5;i++)
    {
        for(int j=i+1;j<=5;j++)
        {
            if(a[i]>a[j])
            {
                m=a[i];
                a[i]=a[j];
                a[j]=m;
            }
        }
    }
    for(int i=1;i<5;i++)
    {if(a[i]!=a[i+1]) count++;}
    printf("%d\n",count);
    return 0;
}