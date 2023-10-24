#include <limits.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main()
{
    int Y;
    int f;
    scanf("%d", & Y);
    f = 0;
    
    if(Y % 4 == 0)
        f = 1;
    else
        ;
    
    if(Y % 100 == 0)
        f = 0;
    else
        ;
    
    if(Y % 400 == 0)
        f = 1;
    else
        ;
    puts((Y % 400 == 0 || (Y % 4 == 0 && Y % 100 != 0)) ? "YES" : "NO");
}