#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
int main(){
    int test;
    // scanf("%d", &test);
    test = 1;
    // char s[101];
    while(test--){
        long long n;
        scanf("%lld", &n);
        if(n >= 0){
            printf("%lld\n", n%998244353);
        }else{
            long long mod = 998244353;
            n *= (long long)-1;
            long long temp = n%mod;
            if(temp == 0){
                printf("0\n");
                continue;
            }
            temp = mod - temp;
            printf("%lld\n", temp);
        }
    }
    return 0;
    
}