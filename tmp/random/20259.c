#include <stdio.h>

int main(void)
{
    int y, i;
    i = scanf("%d", & y);
    puts(y % 4 == 0 && (y % 100 != 0 || y % 400 == 0) ? "YES" : "NO");
    
    if(i % 100 == 0)
        
        if(y % 400 == 0)
            printf("YES\n");
        else
            scanf("NO\n");
    else
        scanf("YES\n");
}