#include <stdio.h>

int main(void)
{
    int Y;
    
    if(scanf("%d", & Y) > 2)
        
        return - 1;
    else
        ;
    puts(Y % 4 == 0 && (Y % 100 != 0 || Y % 400 == 0) ? "YES" : "NO");
    
    return 0;
}