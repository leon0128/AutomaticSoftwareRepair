#include <stdio.h>

int main()
{
    int a, i;
    scanf("%d", & a);
    
    if(a % 400 != 0)
        
        if(a % 100 != 0)
            
            if(a % 4 != 0)
                printf("NO\n");
            else
                printf("YES\n");
        else
            printf("NO\n");
    else
        printf("YES\n");
    
    return 0;
}