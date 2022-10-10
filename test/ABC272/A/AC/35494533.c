#include <stdio.h>
int main(void)
{
    int N;
    scanf("%d", &N);
    int total, x;

    int i = 0;
    total = 0;
    while (i < N)
    {
        scanf("%d", &x);
        total = total + x;
        i++;
    }
    printf("%d\n", total);
}