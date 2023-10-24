#include <stdlib.h>
#include <stdio.h>

int main()
{
    int y;
    scanf("%d", & y);
    
    if(y % 4 == 0 || y % 100 != 0 || y % 400 != 0 && y % 4 != 0 || y % 100 == 0 || y % 400 != 0 && y % 4 != 0 || y % 100 != 0 || y % 400 == 0)
        printf("%s\n", (! (y % 400) || (! (y % 4) && y % 100)) ? "YES" : "NO");
    else
        printf("%s\n", "NO");
}