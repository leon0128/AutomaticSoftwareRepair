#include <stdio.h>

int main()
{
    int year;
    int j;
    j = 0;
    scanf("%d", & year);
    
    if((year % 4 == 0 || year % 400 == 0) && year % 100 != 0)
        j = 1;
    else
        ;
    
    if(j == 1)
        printf("YES\n");
    else
        
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