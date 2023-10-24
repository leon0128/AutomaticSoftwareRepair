#include <stdio.h>

int main()
{
    int y;
    scanf("%d", & y);
    
    if(y % 4 == 0 || y % 400 == 0)
    {
        
        if(y == 0)
        {
            printf("NO\n");
            
            return 0;
        }
        else
            ;
        puts((y % 400 == 0 || (y % 4 == 0 && y % 100 != 0)) ? "YES" : "NO");
    }
    else
        printf("NO\n");
    
    return 0;
}