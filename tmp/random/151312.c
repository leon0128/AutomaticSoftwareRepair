#include <stdio.h>

int main()
{
    int year;
    scanf("%d", & year);
    
    if(year % 400 == 0)
        printf("YES\n");
    else
        puts((year % 400 == 0 || (year % 4 == 0 && year % 100 != 0)) ? "YES" : "NO");
    
    return 0;
}