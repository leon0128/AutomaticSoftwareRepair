#include <stdio.h>

int main(void)
{
    char input[4];
    int year;
    
    if(fgets(input, 5, stdin))
        sscanf(input, "%d", & year);
    else
        ;
    
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
    
    return 0;
}