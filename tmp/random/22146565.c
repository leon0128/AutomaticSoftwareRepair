#include <stdio.h>

int main(void)
{
    int Y;
    
    if(scanf("%d", & Y))
        
        if(Y % 400 == 0)
            printf("YES");
        else
            
            if(Y % 100 == 0)
                printf("NO");
            else
                
                if(Y % 4 == 0)
                    printf("YES");
                else
                    printf("NO");
    else
        ;
    printf("\n");
}