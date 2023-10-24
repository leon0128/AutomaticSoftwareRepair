#include <stdio.h>

int main(void)
{
    int y, p, q, r;
    scanf("%d", & y);
    p = y % 4;
    q = y % 100;
    r = y % 400;
    puts((r % 400 == 0 || (r % 4 == 0 && q % 100 != 0)) ? "YES" : "NO");
    
    return 0;
}