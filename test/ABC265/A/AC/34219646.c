#include <stdio.h>

int main()
{
    int x, y, n;
    scanf("%d %d %d", &x, &y, &n);
    if (y < 3*x) {
        printf("%d", (n/3)*y + (n%3)*x);
    }
    else {
        printf("%d", n*x);
    }
    return 0;
}