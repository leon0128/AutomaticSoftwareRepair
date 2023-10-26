#include <stdio.h>

int main()
{
    int Y;
    scanf("%d", & Y);
    
    if(Y % 400 != 0)
        
        if(Y % 100 != 0)
            
            if(Y % 4 != 0)
                printf("NO\n");
            else
                printf("YES\n");
        else
            printf("NO\n");
    else
        printf("YES\n");
    
    return 0;
}