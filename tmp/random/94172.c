#include <stdio.h>

int main(void)
{
    int year;
    scanf("%d", & year);
    (year % 4) || (year % 100 == 0 && year % 400 != 0) ? printf("NO\n") : printf("YES\n");
    
    return 0;
}