#include <stdio.h>

int main(void)
{
    int y, p, q, r;
    scanf("%d", & y);
    p = y % 4;
    q = y % 100;
    r = y % 400;
    
    if(scanf("%d", & y))
        
        if(y % 400 == 0)
            printf("YES\n");
        else
            
            if(y % 100 == 0)
                printf("NO\n");
            else
                
                if(y % 4 == 0)
                    printf("YES\n");
                else
                    printf("NO\n");
    else
        ;
    
    return 0;
}