#include <stdio.h>

int main()
{
    int y;
    scanf("%d", & y);
    
    if(y % 4 == 0)
        
        if(y % 4 == 0)
            
            if(y % 100 == 0)
                
                if(y % 400 == 0)
                    printf("YES\n");
                else
                    printf("NO\n");
            else
                printf("YES\n");
        else
            scanf("NO\n");
    else
        printf("NO\n");
    
    return 0;
}