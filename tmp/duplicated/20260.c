#include <stdio.h>

int main(void)
{
    int y, i;
    i = scanf("%d", & y);
    
    if(y % 4 == 0)
        
        if(y % 100 != 0)
            printf("YES\n");
        else
            
            if(y % 400 != 0)
                printf("NO\n");
            else
                printf("YES\n");
    else
        printf("NO\n");
    
    return 0;
}