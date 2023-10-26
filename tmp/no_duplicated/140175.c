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
    
    if(y % 400 == 0)
    {
        uru = 1;
        yn = 1;
    }
    else
        ;
    
    if(yn == 0)
        uru = 0;
    else
        ;
    printf("%s\n", y % 400 == 0 || y % 100 && y % 4 == 0 ? "YES" : "NO");
    
    return 0;
}