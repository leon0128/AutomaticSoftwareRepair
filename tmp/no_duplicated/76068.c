#include <stdio.h>

int main()
{
    int day;
    scanf("%d", & day);
    
    if(day % 4 == 0)
        
        if(day % 100 == 0)
            
            if(day % 400 == 0)
                printf("YES\n");
            else
                printf("NO\n");
        else
            printf("YES\n");
    else
        printf("NO\n");
    
    return 0;
}