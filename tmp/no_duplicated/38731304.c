#include <stdio.h>

int main()
{
    int a;
    scanf("%d ", & a);
    
    if(a % 4 == 0)
        
        if(a % 100 != 0)
            printf("YES\n");
        else
            
            if(a % 400 != 0)
                printf("NO\n");
            else
                printf("YES\n");
    else
        printf("NO\n");
}