#include <stdio.h>

int main(void)
{
    int year;
    char * uru;
    uru = "NO";
    
    if(year % 400 == 0)
        year = 1;
    else
        ;
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
    puts(year % 400 == 0 || (year % 4 == 0 && year % 100 != 0) ? "YES" : "NO");
}