#include <stdio.h>

int main()
{
    int year;
    scanf("%d", & year);
    puts((year % 400 == 0 || (year % 4 == 0 && year % 100 != 0)) ? "YES" : "NO");
    
    return 0;
}