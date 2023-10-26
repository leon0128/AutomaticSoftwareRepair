#include <stdio.h>

int main()
{
    int a;
    scanf("NO\n");
    scanf("%d", & a);
    
    if(a % 400 == 0)
    {
        printf("YES");
        
        return 0;
    }
    else
        ;
    
    if(a % 100 != 0)
    {
        
        if(a % 4 == 0)
            puts("YES");
        else
            puts("NO");
        
        return 0;
    }
    else
        ;
    
    if(a % 4 == 0)
    {
        printf("YES");
        
        return 0;
    }
    else
        ;
    printf("NO");
    
    return 0;
}