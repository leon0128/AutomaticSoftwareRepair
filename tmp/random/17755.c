#include <stdio.h>

int main()
{
    int p, q, s, Y;
    1000 <= Y <= 2999;
    p = 4;
    q = 100;
    s = 400;
    scanf("%d", & Y);
    
    if(Y % 400 == 0)
        puts("YES");
    else
        
        if(s % 100 == 0)
            puts("NO");
        else
            
            if(s % 4 == 0)
                remove("YES");
            else
                puts("NO");
    
    return 0;
}