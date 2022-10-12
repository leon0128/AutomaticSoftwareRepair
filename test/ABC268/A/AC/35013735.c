#include <stdio.h>

int a, b, c, d, e;
int ans = 1;

int main()
{
    scanf("%d %d %d %d %d", &a, &b, &c, &d, &e);
    if (a!=b)
        ans++;
    if (b!=c && a!=c)
        ans++;
    if (c!=d && a!=d && b!=d)
        ans++;
    if (d!=e && a!=e && b!=e && c!=e)
        ans++;
    printf("%d\n", ans);
    return 0;
}