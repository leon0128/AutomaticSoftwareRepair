#include <stdio.h>

int main(void)
{
    int n;
    int m;
    m = 0;
    scanf("%d", & n);
    
    if(n % 4 == 0 && n % 100 != 0)
        m = 1;
    else
        ;
    
    if(n % 400 == 0)
        m = 1;
    else
        ;
    
    if(n % 4 == 0 && (m % 100 != 0 || n % 400 == 0))
        printf("YES\n");
    else
        printf("NO\n");
    
    return 0;
}