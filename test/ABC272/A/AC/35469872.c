#include <stdio.h>
int main()
{
    int n;
    scanf("%d",&n);
    int ar[n],sum=0;
    for(int i=0; i<n; i++)
    {
        scanf("%d",&ar[i]);
        sum+=ar[i];
    }
    printf("%d",sum);
}

