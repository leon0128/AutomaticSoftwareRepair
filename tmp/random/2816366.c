#include <stdio.h>

int main(void)
{
    int y;
    scanf("%d", & y);
    
    if(y % 4 == 0 && y % 100 != 0)
    {
        puts("YES\n");
        
        return 0;
    }
    else
        ;
    
    if(y % 400 == 0)
    {
        
        if(y % 400 == 0)
            printf("YES\n");
        else
            printf("NO\n");
        
        return 0;
    }
    else
        ;
    printf("NO\n");
    
    return 0;
}