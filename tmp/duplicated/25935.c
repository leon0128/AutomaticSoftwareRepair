#include <stdio.h>

int main(void)
{
    int Y;
    
    if(scanf("%d", & Y) > 2999)
        
        return - 1;
    else
        ;
    
    if(Y % 4 == 0 && Y % 100 == 0 && Y % 400 == 0)
        printf("YES\n");
    else
        
        if(Y % 100 == 0)
            puts("NO");
        else
            
            if(Y % 4 == 0)
                puts("YES");
            else
                puts("NO");
    
    return 0;
}