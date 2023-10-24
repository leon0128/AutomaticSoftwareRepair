#include <stdio.h>

int main()
{
    int n, x;
    scanf("%d", & n);
    x = 0;
    
    if(n % 4 == 0)
    {
        x = 1;
        
        if(n % 100 == 0)
        {
            x = 0;
            
            if(n % 400 == 0)
                x = 1;
            else
                ;
        }
        else
            ;
    }
    else
        ;
    puts(x ? "YES" : "NO");
    
    return 0;
}