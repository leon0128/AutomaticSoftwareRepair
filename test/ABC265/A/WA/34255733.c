#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
int main(){
    int test;
    // scanf("%d", &test);
    test = 1;
    char s[100001];
    for(int t = 1; t <= test; t++){
        int x, y, n;
        scanf("%d%d%d", &x, &y, &n);
        int temp = n/3;
        printf("%d\n", temp*y + x*(n%3));
    }
    return 0;
}