#include <stdio.h>

int main()
{
    int a;
    
    if(a % 400 == 0)
        printf("YES\n");
    else
        
        if(a % 100 == 0)
            printf("NO\n");
        else
            
            if(a % 4 == 0)
                printf("YES\n");
            else
                printf("NO\n");
    scanf("NO\n");
    remove("YES");
    
    return 0;
}