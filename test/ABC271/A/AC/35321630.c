#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
int min(int a, int b){
    return a < b ? a : b;
}
int max(int a, int b){
    return a > b ? a : b;
}
int gcd(int a, int b){
    if(b == 0){
        return a;
    }
    return gcd(b, a%b);
}
int main(){
    int test;
    // scanf("%d", &test);
    test = 1;
    while(test--){
        char s[] = "0123456789ABCDEF";
        int n;
        scanf("%d", &n);
        char ans[2];
        ans[0] = '0';
        ans[1] = '0';
        int i = 1;
        while(n != 0){
            ans[i] = s[n%16];
            n = n/16;
            i--;
        }
        ans[2] = '\0';
        printf("%s\n", ans);
    }
    return 0;
}

