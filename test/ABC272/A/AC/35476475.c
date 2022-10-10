#include<stdio.h>

int main()
{
    long long int n, a, sum= 0;
    scanf("%lld", &n);

    for(int i=1; i<=n; i++)
    {
        scanf("%lld", &a);
        sum+= a;
    }

    printf("%lld\n", sum);
    return 0;
}
