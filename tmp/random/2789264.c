#include <stdio.h>

int main()
{
    int a, i;
    scanf("%d", & a);
    
    if(a % 4 == 0 || a % 400 == 0)
        
        if(i % 4 == 0 && (a % 100 != 0 || a % 400 == 0))
            printf("YES\n");
        else
            printf("NO\n");
    else
        printf("NO\n");
    
    return 0;
}