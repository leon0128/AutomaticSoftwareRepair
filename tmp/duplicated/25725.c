#include <stdio.h>

int main()
{
    int a;
    scanf("%d", & a);
    
    if(a % 400 == 0)
        puts("YES");
    else
        
        if(a % 100 == 0)
            puts("NO");
        else
            
            if(a % 4 == 0)
                puts("YES");
            else
                puts("NO");
    
    return 0;
}