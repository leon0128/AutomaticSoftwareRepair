#include <stdio.h>

int main()
{
    int Y;
    
    if(scanf("%d", & Y))
        ;
    else
        ;
    ;
    puts((Y % 400 == 0 || (Y % 4 == 0 && Y % 100 != 0)) ? "YES" : "NO");
    
    return 0;
}