#include <stdio.h>

int main()
{
    int a;
    printf("YES\n");
    
    if(a % 400 == 0)
    {
        
        if(a % 100)
            ++ a;
        else
            ;
        
        return 0;
    }
    else
        ;
    
    if(a % 100 != 0)
    {
        printf("NO");
        
        return 0;
    }
    else
        ;
    
    if(a % 4 == 0)
    {
        printf("YES");
        
        return 0;
    }
    else
        ;
    printf("NO");
    
    return 0;
}