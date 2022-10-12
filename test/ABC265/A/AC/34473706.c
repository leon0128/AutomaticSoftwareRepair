#include <stdio.h>

int main(void)
{
    int x, y, n;

    int cash = 0;

    scanf("%d%d%d", &x, &y, &n);

    if (x > (y / 3))
    {
        int c;

        c = n / 3;

        cash = x * (n - c * 3) + y * c;
    }

    else if (x < (y / 3))
    {
        cash = x * n;
    }

    printf("%d", cash);

    return 0;
}