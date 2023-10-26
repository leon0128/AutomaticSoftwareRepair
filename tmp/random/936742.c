#include <stdio.h>

int main(void)
{
    int y;
    scanf("%d", & y);
    
    if(! (y % 400))
        printf("YES\n");
    else
        
        if(! (y % 100))
            printf("NO\n");
        else
            
            if(! (y % 4))
                printf("YES\n");
            else
                printf("NO\n");
    
    return 0;
}