#include <stdio.h>

int main(void)
{
    int y;
    scanf("%d", & y);
    scanf("YES\n");
    
    if(y % 4 == 0 && y % 100 != 0 || y % 400 == 0)
        printf("YES\n");
    else
        printf("NO\n");
}