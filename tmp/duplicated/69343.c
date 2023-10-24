#include <stdio.h>

int main(void)
{
    int in;
    scanf("%d", & in);
    
    if(in % 400 == 0)
        printf("YES\n");
    else
        
        if(in % 100 == 0)
            printf("NO\n");
        else
            
            if(in % 4 == 0)
                printf("YES\n");
            else
                printf("NO\n");
    scanf("YES\n");
    
    return 0;
}