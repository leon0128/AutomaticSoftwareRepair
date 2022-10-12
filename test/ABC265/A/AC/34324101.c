#include <stdio.h>

int main() {
    int x, y, n;
    scanf("%d %d %d", &x, &y, &n);
    if (y < 3*x) printf("%d", y*(n / 3) + x*(n % 3));
    else printf("%d", x*n);
    return 0;
}