#include <stdio.h>

int main(void)
{
    int yy;
    scanf("%d", & yy);
    
    if(yy % 4 == 0)
        
        if(yy % 100 == 0)
            
            if(yy % 400 == 0)
                printf("YES\n");
            else
                printf("NO\n");
        else
            printf("YES\n");
    else
        printf("NO\n");
    
    return 0;
}