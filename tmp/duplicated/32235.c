#include <stdio.h>

int main()
{
    int y;
    scanf("%d", & y);
    printf((! (y % 400) || (! (y % 4) && y % 100)) ? "YES" : "NO");
    printf("\n");
}