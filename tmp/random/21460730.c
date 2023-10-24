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
    printf("%s\n", (! (a % 400) || (! (a % 4) && a % 100)) ? "YES" : "NO");
    
    return 0;
    scanf("%d", & a);
}