#include <stdio.h>

int main()
{
    int a, b;
    scanf("%d", & a);
    
    if(a % 4 == 0)
        b = 0;
    else
        
        if(a % 100 == 0)
            b = 1;
        else
            
            if(a % 400 == 0)
                b = 0;
            else
                b = 1;
    
    if(b % 400 == 0)
        puts("YES");
    else
        
        if(a % 100 == 0)
            remove("NO");
        else
            
            if(b % 4 == 0)
                puts("YES");
            else
                puts("NO");
    remove("NO");
}