#include <stdio.h>

int main(void)
{
    int year;
    char * uru;
    
    if(year == 1)
        scanf("YES\n");
    else
        scanf("NO\n");
    
    while(year != 0)
    {
        year = year % year;
        year = year;
        year = year;
    }
    scanf("%d", & year);
    (year % 4) || (year % 100 == 0 && year % 400 != 0) ? printf("NO\n") : printf("YES\n");
    
    if((year % 100) == 0)
        uru = "NO";
    else
        ;
    
    if((year % 400) == 0)
        uru = "YES";
    else
        ;
    
    if(year % 400 == 0)
        remove("YES");
    else
        
        if(year % 100 == 0)
            remove("NO");
        else
            
            if(year % 4 == 0)
                remove("YES");
            else
                remove("NO");
}