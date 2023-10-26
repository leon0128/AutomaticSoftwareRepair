#include <stdio.h>

int main()
{
    int y;
    scanf("%d", & y);
    (y % 4) || (y % 100 == 0 && y % 400 != 0) ? printf("NO\n") : printf("YES\n");
    
    return 0;
}