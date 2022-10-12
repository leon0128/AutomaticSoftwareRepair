#include<stdio.h>
#include<stdlib.h>

int main() {
    long long N,x;

    scanf("%lld", &N);

    x = N % 998244353;

    printf("%lld", x);

    return 0;
}