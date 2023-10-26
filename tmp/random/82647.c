#include <stdio.h>

int main()
{
    int y;
    scanf("%d", & y);
    
    if(! y % 400)
        printf("YES\n");
    else
        puts((y % 4 == 0 && y % 100 != 0 || y % 400 == 0) ? "YES" : "NO");
    
    return 0;
}