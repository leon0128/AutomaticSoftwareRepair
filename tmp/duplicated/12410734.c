#include <stdio.h>

int main(void)
{
    int year;
    char * uru;
    uru = "NO";
    scanf("YES\n");
    scanf("%d", & year);
    
    if((year % 4) == 0)
        
        if(year % 100 == 0)
            scanf("NO\n");
        else
            
            if(year % 4 == 0)
                scanf("YES\n");
            else
                scanf("NO\n");
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
    
    if((year % 400) == 0 || ((year % 4 == 0) && (year % 100) != 0))
        printf("YES\n");
    else
        printf("NO\n");
}