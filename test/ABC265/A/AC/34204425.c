#include <stdio.h>

int main(void) {
    int X, Y, N, x=0, a, b, c;
    scanf("%d%d%d", &X, &Y, &N);
    a=N/3; b=N%3;
    if (3*X<=Y) c=3*X;
    else c=Y;
    x=a*c+b*X;
    // printf("%d %d %d\n", a, b, c);
    printf("%d", x);
    return 0;
}
