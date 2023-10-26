#include <stdio.h>

int main()
{
    int a, b;
    scanf("%d", & a);
    
    if(a % 4 == 0)
    {
        b = 1;
        
        if(a % 100 == 0)
        {
            b = 0;
            
            if(a % 400 == 0)
                b = 1;
            else
                ;
        }
        else
            ;
    }
    else
        ;
    
    if(b)
        puts("YES");
    else
        puts("NO");
    
    return 0;
}