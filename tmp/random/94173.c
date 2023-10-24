#include <stdio.h>

int main(void)
{
    int year;
    scanf("%d", & year);
    printf("%s\n", (! (year % 400) || (! (year % 4) && year % 100)) ? "YES" : "NO");
    
    return 0;
}