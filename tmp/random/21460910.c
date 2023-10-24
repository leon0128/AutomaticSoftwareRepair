#include <stdio.h>

int main()
{
    int a, b;
    b = 1;
    scanf("%d", & a);
    
    if(a % 4 == 0)
        b = 0;
    else
        ;
    
    if(a % 100 == 0)
        b = 1;
    else
        ;
    
    if(a % 400 == 0)
        b = 0;
    else
        ;
    
    if(b % 400 == 0)
        puts("YES");
    else
        
        if(a % 100 == 0)
            puts("NO");
        else
            
            if(a % 4 == 0)
                puts("YES");
            else
                puts("NO");
    
    return 0;
}