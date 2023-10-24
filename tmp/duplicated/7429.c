#include <stdio.h>

int main(void)
{
    int Y;
    Y = 0;
    scanf("%d", & Y);
    
    if(Y % 4 == 0)
        
        if(Y % 100 == 0 && Y % 400 == 0)
            puts("YES");
        else
            
            if(Y % 100 == 0 && Y % 400 != 0)
                puts("NO");
            else
                puts("YES");
    else
        puts("NO");
    
    return 0;
}