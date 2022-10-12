#include <stdio.h>

int main(void)
{
    int _;
    int x, y, n;
    int x_place, y_place;
    _ = scanf("%d %d %d", &x, &y, &n);
    x_place = x*n;
    y_place = y*(n/3) + x*(n%3);
    if (x_place < y_place)
        printf("%d\n", x_place);
    else
        printf("%d\n", y_place);
    return 0;
}