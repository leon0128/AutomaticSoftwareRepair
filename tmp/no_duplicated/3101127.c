#include <stdio.h>

int main(void)
{
    int n;
    scanf("%d", & n);
    
    if(n % 4 == 0 || n % 100 == 0 || n % 400 == 0)
        
        if(n % 4 == 0)
            
            if(n % 100 == 0)
                
                if(n % 400 == 0)
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