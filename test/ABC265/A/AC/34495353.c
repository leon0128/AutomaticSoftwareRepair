#include <stdio.h>

int main(void)
{
    int x, y, n;
    int cash = 0;

    scanf("%d%d%d", &x, &y, &n);

    if (x < y / 3)
    {
        cash = x * n;
    }

    else if (x > y / 3)
    {
        cash = y * (n / 3) + x * (n % 3);
    }

    printf("%d\n", cash);

    return 0;
}