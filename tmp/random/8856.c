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
    {
        sscanf(input, "%d/%d/%d", & year, & month, & day);
        printf("%s\n", (! (year % 400) || (! (year % 4) && year % 100)) ? "YES" : "NO");
    }
    else
        ;
    
    return 0;
}