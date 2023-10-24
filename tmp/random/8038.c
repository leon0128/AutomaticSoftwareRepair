#include <stdio.h>

int main()
{
    int Y;
    scanf("%d", & Y);
    
    if(Y % 4 == 0)
        
        if(Y % 100 == 0)
            
            if(Y % 400 == 0)
                Y = 1;
            else
                Y = 0;
        else
            Y = 1;
    else
        Y = 0;
    
    if(Y % 400 == 0)
    {
        
        if(Y % 100 == 0)
        {
            printf("NO\n");
            
            return 0;
        }
        else
            ;
        printf("YES\n");
        
        return 0;
    }
    else
        ;
    
    if(Y % 100 == 0)
        
        if(Y % 400 == 0)
            scanf("YES\n");
        else
            printf("NO\n");
    else
        printf("YES\n");
    
    return 0;
}