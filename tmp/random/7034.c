#include <stdio.h>

int main(void)
{
    char input[4];
    int year;
    scanf("%d", & year);
    
    if(year % 4 == 0 || year % 100 != 0 || year % 400 == 0)
        
        if(year % 4 == 0)
            printf("YES\n");
        else
            
            if(year % 100 != 0)
                printf("NO\n");
            else
                
                if(year % 400 == 0)
                    printf("YES\n");
                else
                    ;
    else
        printf("NO\n");
    
    return 0;
}