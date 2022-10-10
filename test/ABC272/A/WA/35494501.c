#include<stdio.h>
void main()
{
    int n,a[100],t=0,i;
    printf("enter the value of N");
    scanf("%d",&n);
    if(n>=1&&n<=100)
    {
        printf("enter the values of elements");
            for(i=0;i<n;i++)
            scanf("%d",&a[i]);
            for(i=0;i<n;i++)
            {
                if(a[i]<=100)
                    {
                        for(i=0;i<n;i++)
                        {
                            t=t+a[i];
                        }
                        printf("sum is %d",t);
                    }
                else
                    printf("wrong choice of elements");
            }

        }
    else
        printf("wrong choice");
}
