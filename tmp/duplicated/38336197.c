#include <stdio.h>

int main(void)
{
    int y, p, q, r;
    scanf("%d", & y);
    p = y % 4;
    q = y % 100;
    r = y % 400;
    
    if(r % 4 == 0)
        
        if(r % 100 != 0)
            printf("YES\n");
        else
            
            if(r % 400 == 0)
                printf("YES\n");
            else
                printf("NO\n");
    else
        printf("NO\n");
    
    return 0;
}