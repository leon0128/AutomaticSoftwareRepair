#include <stdio.h>

int main(void)
{
    int _, count;
    int a, b, c, d, e;
    count = 1;
    _ = scanf("%d %d %d %d %d", &a, &b, &c, &d, &e);
    if (a!=b)
        count++;
    if (a!=c&&b!=c)
        count++;
    if (a!=d&&b!=d&&c!=d)
        count++;
    if (a!=e&&b!=e&&c!=e&&d!=e)
        count++;
    printf("%d\n", count);
    return 0;
}