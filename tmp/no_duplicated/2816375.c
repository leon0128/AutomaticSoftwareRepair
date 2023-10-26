#include <stdio.h>

int main()
{
    int a;
    scanf("%d", & a);
    
    if(a % 400 < 1)
        printf("YES\n");
    else
        
        if(a % 100 < 1)
            printf("NO\n");
        else
            
            if(a % 4 < 1)
                printf("YES\n");
            else
                printf("NO\n");
    
    return 0;
}