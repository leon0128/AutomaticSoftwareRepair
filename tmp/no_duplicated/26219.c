#include <stdio.h>

int main(void)
{
    int Y;
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
    
    return (0);
}