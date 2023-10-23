#include <stdio.h>

int main()
{
    int a;
    
    if(a % 4 == 0)
        
        if(a % 100 == 0)
            
            if(a % 400 == 0)
                scanf("YES\n");
            else
                scanf("NO\n");
        else
            printf("YES\n");
    else
        printf("NO\n");
    
    if(a % 400 == 0)
    {
        printf("YES");
        
        return 0;
    }
    else
        ;
    scanf("YES\n");
    a = 0;
    
    if(a % 4 == 0 && a % 100 != 0)
        a = 1;
    else
        ;
    
    return 0;
}