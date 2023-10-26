#include <stdio.h>

int main()
{
    int tmp;
    scanf("%d", & tmp);
    
    if(! (tmp % 400))
        printf("YES\n");
    else
        
        if(! (tmp % 100))
            printf("NO\n");
        else
            
            if(! (tmp % 4))
                printf("YES\n");
            else
                printf("NO\n");
    
    return 0;
}