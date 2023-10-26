#include <stdio.h>

int main(void)
{
    int yy;
    scanf("%d", & yy);
    
    if(yy % 400 == 0)
        puts("YES");
    else
        
        if(yy % 100 == 0)
            puts("NO");
        else
            
            if(yy % 4 == 0)
                puts("YES");
            else
                puts("NO");
    
    return 0;
}