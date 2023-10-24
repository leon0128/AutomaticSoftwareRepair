#include <stdio.h>

int main()
{
    int tmp;
    scanf("%d", & tmp);
    
    if(tmp % 400 == 0)
        printf("YES\n");
    else
        
        if(tmp % 4 == 0)
            
            if(tmp % 100 != 0)
                printf("YES\n");
            else
                printf("NO\n");
        else
            printf("NO\n");
    
    return 0;
}