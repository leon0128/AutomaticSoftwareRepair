#include <stdio.h>
int main()
{
    int x, y, n, tm;
    scanf("%d%d%d", &x, &y, &n);

    if (3 * x < y || n < 3)
    {
        printf("%d", x * n);
    }
    else if (3 * x > y && n >= 3)
    {
        int d = n / 3;
        int m = n % 3;
        if (m == 0)
        {
            printf("%d", d * y);
        }
        else
        {
            int ta = (d * y) + (m * x);
            printf("%d", ta);
        }
    }
}
