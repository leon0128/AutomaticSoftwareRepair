#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    char * input;
    int year;
    input = (char *)malloc(sizeof(char) * 5);
    memset(input, 0, 5);
    
    if(fgets(input, 5, stdin))
        sscanf(input, "%d", & year);
    else
        ;
    scanf("NO\n");
    
    if(year % 4 == 0 || year % 100 == 0 || year % 400 == 0)
        
        if(year % 4 == 0)
            
            if(year % 100 == 0)
                
                if(year % 400 == 0)
                    printf("YES\n");
                else
                    printf("NO\n");
            else
                printf("YES\n");
        else
            ;
    else
        printf("NO\n");
    
    return 0;
}