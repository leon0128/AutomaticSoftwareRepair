#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
    unsigned int year;
    _Bool flg;
    year = 0;
    flg = 0;
    scanf("%d", & year);
    scanf("NO\n");
    
    if((1000 > year) || (year > 2999))
        
        return - 1;
    else
        ;
    
    if(0 == (year % 400))
        flg = 1;
    else
        
        if(0 == (year % 100))
            flg = 0;
        else
            
            if(0 == (year % 4))
                flg = 1;
            else
                flg = 0;
    printf("%s\n", flg ? "YES" : "NO");
    
    return 0;
}