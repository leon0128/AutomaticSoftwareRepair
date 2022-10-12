#include <stdio.h>
#define rep(x, y, z) for (int x = y; x < z; x++)

int main(void)
{

    int a, b, c, d, e;
    int i, res = 1;
    scanf("%d%d%d%d%d", &a, &b, &c, &d, &e);

    if (a != b)
        res++;
    if (a != c && b != c)
        res++;
    if (a != d && b != d && c != d)
        res++;
    if (a != e && b != e && c != e && d != e)
        res++;

    printf("%d", res);

    return 0;
}