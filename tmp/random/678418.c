#include <stdio.h>

int main(void)
{
    int y;
    scanf("%d", & y);
    
    if(y % 400 != 0)
        
        if(y % 100 != 0)
            
            if(y % 4 != 0)
                printf("NO\n");
            else
                printf("YES\n");
        else
            printf("NO\n");
    else
        printf("YES\n");
    
    return 0;
}