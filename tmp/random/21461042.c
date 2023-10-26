#include <stdio.h>

int main()
{
    int year;
    year = 2404;
    scanf("%d", & year);
    
    if(year % 4 == 0)
        
        if(year % 100 == 0)
            
            if(year % 400 == 0)
                printf("YES\n");
            else
                printf("NO\n");
        else
            printf("YES\n");
    else
        printf("NO\n");
}