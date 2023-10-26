#include <stdio.h>

int main(void)
{
    int y;
    scanf("%d", & y);
    
    if(y % 400 == 0)
        printf("YES\n");
    else
        printf(y % 4 == 0 ? (y % 100 == 0 ? (y % 400 == 0 ? "YES\n" : "NO\n") : "YES\n") : "NO\n");
    
    return 0;
}