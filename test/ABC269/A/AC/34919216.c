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
int main(){
    int test;
    // scanf("%d", &test);
    test = 1;
    while(test--){
        int a, b, c, d;
        scanf("%d%d%d%d", &a, &b, &c, &d);
        printf("%d\n", (a + b)*(c - d));
        printf("Takahashi");
    }
    return 0;
}

