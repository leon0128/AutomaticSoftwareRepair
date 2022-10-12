#include <stdio.h>
#include <string.h>
 
int main(void)
{
    int X, Y, N;

    scanf("%d %d %d", &X, &Y, &N);

    if (3 * X > Y)
        printf("%d\n", (N / 3) * Y + (N % 3) * X);
    else
        printf("%d\n", N * X);

    return 0;
}