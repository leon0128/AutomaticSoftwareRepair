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
    printf("%s\n", (((n % 400 == 0) ? 1 : (n % 100 == 0) ? 0 : (n % 4 == 0) ? 1 : 0) ? "YES" : "NO"));
    
    return 0;
}