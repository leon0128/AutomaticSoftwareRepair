#include <stdio.h>

int main(void)
{
    int Y;
    
    if(Y % 4 == 0 && (! (Y % 100 == 0) || Y % 400 == 0))
        scanf("%d", & Y);
    else
        printf("NO");
    
    if(Y % 4 != 0)
        printf("NO\n");
    else
        
        if(Y % 4 == 0 && Y % 100 != 0)
            printf("YES\n");
        else
            
            if(Y % 4 == 0 && Y % 100 == 0 && Y % 400 != 0)
                printf("NO\n");
            else
                printf("YES\n");
}