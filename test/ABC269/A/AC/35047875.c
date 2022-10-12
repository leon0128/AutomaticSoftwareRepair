#include <stdio.h>
char str[] = "Takahashi";
int main()
{
    long long  a,b,c,d;
    scanf("%lld%lld%lld%lld",&a,&b,&c,&d);
    printf("%lld\n%s\n",(a+b)*(c-d),str);
    return 0;
}