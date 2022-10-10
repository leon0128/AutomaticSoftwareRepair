#include<stdio.h>
#include<stdlib.h>

int main(void) {
    int N;
    long long x;
    long long sum = 0;
    scanf("%d",&N);
    while(N--){
        scanf("%lld", &x);
        sum += x;
    }
    printf("%lld", sum);
    return 0;
}