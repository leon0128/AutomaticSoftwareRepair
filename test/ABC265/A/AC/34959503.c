#include <stdio.h>

int main(void)
{

    int x, y, n;

    scanf("%d", &x);
    scanf("%d", &y);
    scanf("%d", &n);

    int syou = n / 3;
    int amari = n % 3;

    int ans = syou * y + amari * x;
    if (syou * y + amari * x > x * n)
    {
        ans = x * n;
    }

    printf("%d\n", ans);

    return 0;
}