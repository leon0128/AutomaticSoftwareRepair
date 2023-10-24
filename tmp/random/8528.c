#include <stdio.h>

int main()
{
    int Y, F;
    scanf("%d", & Y);
    
    if(Y % 4 == 0)
    {
        F = 1;
        
        if(Y % 100 == 0 && Y % 400 != 0)
            F = 0;
        else
            ;
    }
    else
        F = 0;
    
    if(F)
        printf("YES\n");
    else
        printf("NO\n");
    
    return 0;
}