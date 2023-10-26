#include <stdio.h>

int main(void)
{
    char input[11];
    int year;
    int month;
    int day;
    double y;
    double m;
    double d;
    double ans;
    double decimal_part;
    
    if(fgets(input, 11, stdin))
        sscanf(input, "%d/%d/%d", & year, & month, & day);
    else
        ;
    
    if(year % 400 == 0)
        puts("YES");
    else
        
        if(year % 100 == 0)
            puts("NO");
        else
            
            if(year % 4 == 0)
                puts("YES");
            else
                puts("NO");
    
    return 0;
}