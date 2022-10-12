#include<stdio.h>
int main()
{
    int a[5],count=0,i,j;
    for(int i=0; i<5; i++)
    {
        scanf("%d",&a[i]);
    }
    for( i=0; i<5; i++)
    {
        for(j=0 ;j<i; j++)
        {


            if(a[i]==a[j])
            {
                break;
            }
        }
        if(i==j)
            count++;
    }
    printf("%d",count);

}
