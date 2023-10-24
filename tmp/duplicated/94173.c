#include <stdio.h>

int main(void)
{
    int year;
    scanf("%d", & year);
    
    if(year % 100 == 0)
        
        if(year % 400 == 0)
            printf("YES\n");
        else
            printf("NO\n");
    else
        
        if(year % 4 == 0)
            printf("YES\n");
        else
            printf("NO\n");
    
    return 0;
}