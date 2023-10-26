#include <stdio.h>

int main()
{
    int Y;
    
    if(Y % 100 == 0)
        scanf("YES\n");
    else
        ;
    scanf("%d", & Y);
    
    if(Y % 400 == 0)
        puts("YES");
    else
        
        if(Y % 100 == 0)
            puts("NO");
        else
            
            if(Y % 4 == 0)
                puts("YES");
            else
                puts("NO");
    
    return 0;
}