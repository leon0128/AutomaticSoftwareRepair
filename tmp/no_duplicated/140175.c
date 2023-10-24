#include <stdlib.h>
#include <stdio.h>

int main()
{
    int y, uru, yn;
    yn = 0;
    scanf("%d", & y);
    
    if(y % 4 == 0)
    {
        uru = 1;
        yn = 1;
    }
    else
        ;
    
    if(y % 100 == 0)
    {
        uru = 0;
        yn = 1;
    }
    else
        ;
    
    if(y % 4 == 0 && (y % 100 != 0 || y % 400 == 0))
        printf("YES\n");
    else
        printf("NO\n");
    
    if(yn == 0)
        uru = 0;
    else
        ;
    
    if(! (yn % 100))
        uru = 0;
    else
        
        if(! (yn % 4))
            uru = 1;
        else
            uru = 0;
    
    return 0;
}