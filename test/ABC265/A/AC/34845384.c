#include<stdio.h>

int main(void) {
    int X, Y, N;
    int ans = 0;
    scanf("%d %d %d", &X, &Y, &N);
    if(X * 3 < Y) {
        ans = X * N;
    } else {
        int a = N / 3;
        int b = N % 3;
        ans = a * Y + b * X;
    }
    printf("%d\n", ans);
    return 0;
}