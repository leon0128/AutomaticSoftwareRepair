#include <stdio.h>

int main(void)
{
    int year;
    char * uru;
    uru = "NO";
    scanf("YES\n");
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
    puts(year % 400 ? year % 100 ? year % 4 ? "NO" : "YES" : "NO" : "YES");
}