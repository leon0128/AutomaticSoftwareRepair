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
        
        if(Y % 400 == 0)
            printf("YES\n");
        else
            
            if(Y % 100 == 0)
                printf("NO\n");
            else
                
                if(Y % 4 == 0)
                    printf("YES\n");
                else
                    printf("NO\n");
    
    return 0;
}