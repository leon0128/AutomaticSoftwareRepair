#include<stdio.h>
int main()
{
    int a, n, s=0, i;
    scanf("%d", &n);
    for(i=1;i<=n;i++)
    {
        scanf("%d", &a);
        s=s+a;
    }
    printf("%d\n", s);
    return 0;
}