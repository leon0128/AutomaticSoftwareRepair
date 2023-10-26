#include <stdio.h>

int main(void)
{
    int y;
    scanf("%d", & y);
    puts(y % 400 == 0 || (y % 4 == 0 && y % 100 != 0) ? "YES" : "NO");
    
    return 0;
}