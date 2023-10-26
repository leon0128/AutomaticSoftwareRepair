#include <stdio.h>

int main(void)
{
    int year;
    char * uru;
    uru = "NO";
    scanf("YES\n");
    scanf("%d", & year);
    
    if((year % 4) == 0)
        scanf("%d", & year);
    else
        ;
    
    if((year % 100) == 0)
        uru = "NO";
    else
        ;
    
    if(year % 4 == 0)
        printf("YES\n");
    else
        printf("NO\n");
}