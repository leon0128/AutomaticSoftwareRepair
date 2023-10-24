#include <stdio.h>

int main(void)
{
    int year;
    char * uru;
    year = 1;
    scanf("%d", & year);
    
    if((year % 4) == 0)
        uru = "YES";
    else
        ;
    
    if((year % 100) == 0)
        uru = "NO";
    else
        ;
    
    if((year % 400) == 0)
        uru = "YES";
    else
        ;
    
    if(year % 400 == 0)
        printf("YES\n");
    else
        
        if(year % 100 == 0)
            printf("NO\n");
        else
            
            if(year % 4 == 0)
                printf("YES\n");
            else
                printf("NO\n");
}