#include <stdlib.h>
#include <stdio.h>

int main()
{
    int i;
    
    if(scanf("%d", & i))
        
        if(i % 400 == 0)
            printf("YES\n");
        else
            
            if(i % 100 == 0)
                printf("NO\n");
            else
                
                if(i % 4 == 0)
                    printf("YES\n");
                else
                    printf("NO\n");
    else
        ;
}