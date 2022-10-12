#include <stdio.h>

int main(void){

    // define
    int i, N, X, Y, money = 0;

    scanf("%d %d %d", &X, &Y, &N);

    if (Y < 3 * X) {
        for (i = N; i >= 3; i-=3) {
            money += Y;
        }
        money += i * X;
    } else {
        money = N * X;
    }

    printf("%d\n", money);

    return 0;
}