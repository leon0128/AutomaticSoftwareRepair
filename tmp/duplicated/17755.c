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
        printf("YES\n");
    else
        
        if(Y % 100 == 0)
            printf("NO\n");
        else
            
            if(Y % 4 == 0)
                printf("YES\n");
            else
                printf("NO\n");
    
    return 0;
}