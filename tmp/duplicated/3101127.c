#include <stdio.h>

int main(void)
{
    int n;
    scanf("%d", & n);
    
    if(n % 400 == 0)
        puts("YES");
    else
        
        if(n % 100 == 0)
            puts("NO");
        else
            
            if(n % 4 == 0)
                puts("YES");
            else
                puts("NO");
    
    return 0;
}