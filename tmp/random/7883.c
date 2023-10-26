#include <stdio.h>

int main(void)
{
    int Y;
    Y = 0;
    scanf("%d", & Y);
    
    if(Y % 400 == 0)
        printf("YES\n");
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