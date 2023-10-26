#include <stdio.h>

int main()
{
    int y, cnt;
    cnt = 0;
    scanf("%d", & y);
    
    if(y % 4 == 0)
        cnt = 1;
    else
        ;
    
    if(y % 100 == 0)
        cnt = 0;
    else
        ;
    
    if(y % 400 == 0)
        cnt = 1;
    else
        ;
    
    if(y % 4)
        printf("NO\n");
    else
        
        if((y % 100) == 0)
            
            if((y % 400) == 0)
                printf("YES\n");
            else
                printf("NO\n");
        else
            printf("YES\n");
    
    return 0;
}