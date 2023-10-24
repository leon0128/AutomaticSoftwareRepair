#include <stdio.h>

int main(void)
{
    int year;
    scanf("%d", & year);
    
    if(! (year % 400))
        printf("YES\n");
    else
        
        if(! (year % 100))
            printf("NO\n");
        else
            
            if(! (year % 4))
                printf("YES\n");
            else
                printf("NO\n");
    
    return 0;
}