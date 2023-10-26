#include <stdio.h>

int main(void)
{
    int Y;
    scanf("%d", & Y);
    
    if(! (Y % 400))
        puts("YES");
    else
        
        if(! (Y % 100))
            puts("NO");
        else
            
            if(! (Y % 4))
                puts("YES");
            else
                puts("NO");
    
    return 0;
}