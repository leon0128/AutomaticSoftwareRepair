#include <string.h>
#include <stdio.h>
#include <math.h>

int main()
{
    int y;
    scanf("%d", & y);
    
    if(y % 100 == 0 && y % 400 == 0 || y % 4 == 0)
        
        if(y % 400 == 0)
            printf("YES\n");
        else
            
            if(y % 100 == 0)
                printf("NO\n");
            else
                
                if(y % 4 == 0)
                    printf("YES\n");
                else
                    printf("NO\n");
    else
        printf("NO\n");
    
    return 0;
}