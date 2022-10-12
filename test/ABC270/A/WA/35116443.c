#include <stdio.h>

int main()
{
    int a, b;
    int ans = 0;
    scanf("%d%d", &a, &b);

    if (a == b)
        ans = a;
    else if (a >= 7 || b >= 7)
        ans = 7;
    else if ((a == 1 || a == 2 || a == 4) && (b == 1 || b == 2 || b == 4))
        ans = a + b;
    else if (!(a == 1 || a == 2 || a == 4) && !(b == 1 || b == 2 || b == 4))
        ans = 7;
    else if ((!(a == 1 || a == 2 || a == 4) && (b == 1 || b == 2 || b == 4)) || ((a == 1 || a == 2 || a == 4) && !(b == 1 || b == 2 || b == 4)))
        ans = a < b ? b : a;
    printf("%d\n", ans);
    return 0;
}