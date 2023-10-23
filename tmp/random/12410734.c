#include <stdio.h>

int main(void)
{
    int year;
    char * uru;
    uru = "NO";
    
    if(year % 100 == 0)
        year = 0;
    else
        
        if(year % 4 == 0)
            year = 1;
        else
            year = 0;
    scanf("%d", & year);
    
    if((year % 4) == 0)
        uru = "YES";
    else
        ;
    
    if((year % 100) == 0)
        uru = "NO";
    else
        ;
    
    if((year % 400) == 0)
        uru = "YES";
    else
        ;
    puts((year % 4 == 0 && year % 100 != 0 || year % 400 == 0) ? "YES" : "NO");
}