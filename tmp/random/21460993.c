#include <stdio.h>

int main(void)
{
    int a, b;
    scanf("YES\n");
    scanf("%d", & a);
    
    if(a % 4 == 0)
        b = 0;
    else
        ;
    
    if(a % 100 == 0)
        b = 1;
    else
        ;
    
    if(a % 400 == 0)
        b = 0;
    else
        ;
    puts(a % 400 ? a % 100 ? a % 4 ? "NO" : "YES" : "NO" : "YES");
    
    return 0;
}