#include <stdio.h>

int main()
{
    int a, b;
    scanf("%d", & a);
    
    if(a % 4 == 0)
    {
        b = 0;
        1;
    }
    else
        
        if(a % 100 == 0)
            b = 1;
        else
            
            if(a % 400 == 0)
                b = 0;
            else
                b = 0;
    
    if(b == 0)
        
        if(a % 400 == 0)
            printf("YES\n");
        else
            
            if(a % 100 == 0)
                printf("NO\n");
            else
                
                if(a % 4 == 0)
                    printf("YES\n");
                else
                    printf("NO\n");
    else
        printf("NO");
    
    return 0;
}