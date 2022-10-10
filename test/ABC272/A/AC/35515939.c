#include<stdio.h>
int main()
{
    int n;
    scanf("%d",&n);
    int a[n+1],sum=0;
    for(int i=0; i<n; i++)
    {
        scanf("%d",&a[i]);
        sum=sum+a[i];
    }
    printf("%d\n",sum);
    return 0;
}
