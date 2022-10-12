#include <stdio.h>
int main(void)
{
    int x, y, n;
    int amari = n % 3;
    scanf("%d %d %d", &x, &y, &n);

    if ((3 * x) < y || n < 3)
        printf("%d\n", x * n);

    else
    {
        if (amari == 0)
            printf("%d\n", (n / 3) * y);

        else if (amari == 1)
            printf("%d\n", (n / 3) * y + x);

        else if (amari == 2)
            printf("%d\n", (n / 3) * y + 2 * x);
    }

    return 0;
}