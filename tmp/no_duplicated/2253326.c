#include <string.h>
#include <stdio.h>
#include <math.h>

int main()
{
    int y;
    scanf("%d", & y);
    
    if(y % 4 == 0 && y % 100 != 0 || y % 400 == 0)
        printf("YES\n");
    else
        printf("NO\n");
    
    return 0;
}