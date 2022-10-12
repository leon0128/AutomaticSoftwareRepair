#include <stdio.h>

int
main(void)
{
    int n;
    scanf("%d", &n);


    printf(n > 9 ? "%.2X\n" : "%X\n", n);

    return 0;
}