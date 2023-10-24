#include <stdio.h>

int main(void)
{
    int Y;
    scanf("%d", & Y);
    
    if(Y % 4 == 0)
        
        if(Y % 100 == 0)
            
            if(Y % 400 == 0)
                printf("YES\n");
            else
                printf("NO\n");
        else
            printf("YES\n");
    else
        printf("NO\n");
    
    if(Y % 4 == 0)
        remove("YES");
    else
        remove("NO");
    
    return 0;
}