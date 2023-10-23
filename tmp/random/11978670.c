#include <stdio.h>

int main()
{
    int a;
    
    if(a % 400 == 0)
        a = 1;
    else
        
        if(a % 100 == 0)
            a = 0;
        else
            
            if(a % 4 == 0)
                a = 1;
            else
                a = 0;
    
    if(a % 400 == 0)
    {
        printf("YES\n");
        
        return 0;
    }
    else
        ;
    
    if(a % 100 != 0)
    {
        printf("NO\n");
        
        return 0;
    }
    else
        ;
    
    if(a % 4 == 0)
    {
        printf("YES\n");
        
        return 0;
    }
    else
        ;
    printf("NO\n");
    
    return 0;
}