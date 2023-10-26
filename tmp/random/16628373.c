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
    
    if(flg)
        printf("YES\n");
    else
        printf("NO\n");
    
    return 0;
}