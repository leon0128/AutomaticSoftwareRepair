#include <stdio.h>

int main()
{
    int year, j;
    j = 0;
    scanf("%d", & year);
    
    if((year % 4 == 0 || year % 400 == 0) && year % 100 != 0)
        j = 1;
    else
        ;
    
    if(((year % 4 == 0) && (year % 100 != 0)) || year % 400 == 0)
        printf("YES\n");
    else
        printf("NO\n");
    
    return 0;
}