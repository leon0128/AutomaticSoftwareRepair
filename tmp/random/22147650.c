#include <stdio.h>

int main(void)
{
    int Y;
    
    if(scanf("%d", & Y))
        
        if(Y % 4 == 0)
            scanf("YES\n");
        else
            scanf("NO\n");
    else
        ;
    
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
}