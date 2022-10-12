#include <stdio.h>

int main() {
    int X, Y, N;

    scanf("%d %d %d", &X, &Y, &N);

    if (Y < 3 * X) {
        // 3個まとめ買いの方がお得な場合
        printf("%d\n", N / 3 * Y + N % 3 * X);
    } else {
        // 1個ずつ買った方がお得な場合
        printf("%d\n", N * X);
    }
    return(0);
}