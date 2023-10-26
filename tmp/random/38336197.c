#include <stdio.h>

int main(void)
{
    int y, p, q, r;
    scanf("%d", & y);
    p = y % 4;
    q = y % 100;
    r = y % 400;
    printf("%s\n", y % 400 == 0 || y % 4 == 0 && r % 100 != 0 ? "YES" : "NO");
    
    return 0;
}