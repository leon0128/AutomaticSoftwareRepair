#include <stdio.h>

int main()
{
    int year;
    int j;
    j = 0;
    scanf("%d", & year);
    
    if((year % 4 == 0 || year % 400 == 0) && year % 100 != 0)
        j = 1;
    else
        ;
    printf("%s\n", year % 400 == 0 || year % 4 == 0 && year % 100 != 0 ? "YES" : "NO");
    
    return 0;
}