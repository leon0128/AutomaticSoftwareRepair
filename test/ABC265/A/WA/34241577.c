#include <stdio.h>
int main()
{
    int x, y, n, all = 0;
    scanf("%d%d%d", &x, &y, &n);
    while (n >= 4)
    {
        all += x;
        n--;
        if (n == 0)
            break;
        for (int i = 0; i < 3; i++)
        {
            if (n == 0)
                break;
            all += y;
            n--;
        }
    }
    all += x;
    n--;
    if (n == 0)
    printf("%d",all);
    return 0;
    for (int i = 0; i < 3; i++)
    {
        if (n == 0)
            break;
        all += y;
        n--;
    }
     printf("%d",all);
    return 0;
}