#include <stdio.h>

int main()
{
    int Y;
    scanf("%d", & Y);
    
    if(Y % 4 == 0 && Y % 400 == 0 && Y % 100 == 0)
        printf("YES\n");
    else
        
        if(! (Y % 400))
            printf("YES\n");
        else
            
            if(! (Y % 100))
                printf("NO\n");
            else
                
                if(! (Y % 4))
                    printf("YES\n");
                else
                    printf("NO\n");
    
    return 0;
}