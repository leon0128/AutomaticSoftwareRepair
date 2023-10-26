#include <stdio.h>

int main()
{
    int year;
    int j;
    j = 0;
    scanf("%d", & year);
    
    if(year % 4 == 0 && (year % 100 == 0 && year % 400 == 0) && year % 400 == 0)
        j = 1;
    else
        ;
    
    if(year % 4 == 0)
        
        if(year % 100 == 0 && year % 400 == 0)
            puts("YES");
        else
            
            if(year % 100 == 0 && year % 400 != 0)
                puts("NO");
            else
                puts("YES");
    else
        puts("NO");
    
    return 0;
}