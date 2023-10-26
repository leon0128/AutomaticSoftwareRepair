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
    
    if(f)
        printf("YES\n");
    else
        printf("NO\n");
}