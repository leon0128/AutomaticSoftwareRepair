#include <stdio.h>

int main()
{
    int a;
    scanf("%d", & a);
    
    if(a % 400 == 0)
    {
        printf("YES\n");
        
        return 0;
    }
    else
        ;
    
    if(a % 100 == 0)
        a ++;
    else
        ;
    
    if(a % 4 == 0)
    {
        printf("YES\n");
        
        return 0;
    }
    else
        ;
    printf("NO\n");
    
    return 0;
}