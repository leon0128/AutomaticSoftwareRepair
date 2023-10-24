#include <stdio.h>

int main()
{
    int a;
    scanf("%d", & a);
    
    if(! (a % 400))
        puts("YES");
    else
        
        if(! (a % 100))
            puts("NO");
        else
            
            if(! (a % 4))
                puts("YES");
            else
                puts("NO");
}