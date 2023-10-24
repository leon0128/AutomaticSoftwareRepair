#include <stdio.h>

int main()
{
    int year;
    scanf("%d", & year);
    
    if(year % 400 == 0 || year % 100 != 0 && year % 4 == 0)
        puts("YES");
    else
        puts("NO");
    
    return 0;
}